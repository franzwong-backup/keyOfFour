// DS.cpp: implementation of the CDS class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\DS.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDS::CDS()
{
	m_hWnd = 0;
	m_hInstance = 0;
	m_lpGraph = 0;
	m_pEvent = 0;
	m_pMediaControl = 0;
	m_bCreate = false;
	m_bLoad = false;
	m_bPlay = false;
}

CDS::~CDS()
{
	CleanUp();
}

bool CDS::Create(HWND hWnd, HINSTANCE hInstance)
{	
	HRESULT hRet;
	hRet = CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(void**)&m_lpGraph);
	if ( FAILED(hRet) ) { return false; }
	hRet = m_lpGraph->QueryInterface(IID_IMediaControl, (void **)&m_pMediaControl);
	if ( FAILED(hRet) ) { return false; }
	hRet = m_lpGraph->QueryInterface(IID_IMediaEvent, (void **)&m_pEvent);
	if ( FAILED(hRet) ) { return false; }

	m_hWnd = hWnd;
	m_hInstance = hInstance;
	m_bCreate = true;
	return true;
}

void CDS::CleanUp()
{
	if ( m_lpGraph ) { m_lpGraph->Release(); m_lpGraph = 0; }
	if ( m_pMediaControl ) { m_pMediaControl->Release(); m_pMediaControl = 0; }
	if ( m_pEvent ) { m_pEvent->Release(); m_pEvent = 0; }
	m_hWnd = 0;
	m_hInstance = 0;
}

bool CDS::LoadSound(const TCHAR* lpszFile)
{
	if ( !m_bCreate ) { return false; }
	if ( m_lpGraph )
	{
		WCHAR wszFile[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, lpszFile, -1, wszFile, MAX_PATH);

		HRESULT hRet = m_lpGraph->RenderFile(wszFile, 0);
		if ( FAILED(hRet) ) { return false; }
		m_bLoad = true;
	}
	return true;
}


bool CDS::PlaySound()
{
	HRESULT hRet;
	if ( !m_bLoad ) { return false; }
	if ( m_pMediaControl )
	{
		hRet = m_pMediaControl->Run();
		if ( FAILED(hRet) ) { return false; }
		m_bPlay = true;
	}
	return true;
}

bool CDS::StopSound()
{
	HRESULT hRet;
	if ( m_bPlay )
	{
		if ( m_pMediaControl )
		{
			hRet = m_pMediaControl->Stop();
			if ( FAILED(hRet) ) { return false; }
		}
		m_bPlay = false;
	}
	return true;
}	

bool CDS::CheckAndLoop()
{	
	long lEventCode;
	long lParam1;
	long lParam2;
	HRESULT hRet = 0;
	if ( m_bPlay )
	{
		if ( m_pEvent )
		{
			while (hRet = m_pEvent->GetEvent(&lEventCode, &lParam1, &lParam2, 0), SUCCEEDED(hRet))
			{ 
				hRet = m_pEvent->FreeEventParams(lEventCode, lParam1, lParam2);
				if ( FAILED(hRet) ) { return false; }
				if ((EC_COMPLETE == lEventCode))
				{ 
					IMediaPosition* pMP;
					hRet = pMP->QueryInterface(IID_IMediaPosition,(void**)&pMP);
					if ( FAILED(hRet) ) { return false; } 
					hRet = pMP->put_CurrentPosition(0);
					if ( FAILED(hRet) ) { return false; }
					pMP->Release();
					pMP = 0;
				} 
			}		
		}
	}
	return true;
}