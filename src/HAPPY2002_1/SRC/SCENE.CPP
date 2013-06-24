// Scene.cpp: implementation of the CScene class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\Scene.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CScene::CScene()
{
}

CScene::CScene(CDD* pDD, HWND hWnd, HINSTANCE hInstance)
{
	m_pDS = new CDS;
	m_hWnd = hWnd;
	m_hInstance = hInstance;
	m_pDD = pDD;
}

CScene::~CScene()
{
	m_pDD = 0;
	m_hWnd = 0;
	m_hInstance = 0;
	if ( m_pDS ) { delete m_pDS; m_pDS = 0; }
}

bool CScene::PlayMusic()
{
	bool bRet;
	bRet = m_pDS->PlaySound();
	if ( !bRet ) { return false; }
	return true;
}

bool CScene::StopMusic()
{
	bool bRet;
	bRet = m_pDS->StopSound();
	if ( !bRet ) { return false; }
	return true;
}

bool CScene::CheckAndLoop()
{
	bool bRet;
	bRet = m_pDS->CheckAndLoop();
	if ( !bRet ) { return false; }
	return true;
}