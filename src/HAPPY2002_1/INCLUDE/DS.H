// DS.h: interface for the CDS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DS_H__18ED7C8A_D462_4301_A266_7A5AD8B65E52__INCLUDED_)
#define AFX_DS_H__18ED7C8A_D462_4301_A266_7A5AD8B65E52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dshow.h>

class CDS  
{
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	IGraphBuilder* m_lpGraph;
	IMediaControl* m_pMediaControl;
	IMediaEvent*   m_pEvent;
	bool m_bCreate;
	bool m_bLoad;
	bool m_bPlay;
public:
	bool CheckAndLoop();
	bool StopSound();
	bool PlaySound();
	bool LoadSound(const TCHAR* lpszFile);
	void CleanUp();
	bool Create(HWND hWnd, HINSTANCE hInstance);
	CDS();
	virtual ~CDS();
//	bool Abort();
};

#endif // !defined(AFX_DS_H__18ED7C8A_D462_4301_A266_7A5AD8B65E52__INCLUDED_)
