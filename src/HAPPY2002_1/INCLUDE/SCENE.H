// Scene.h: interface for the CScene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENE_H__80F81C89_C5FE_40F0_8D8E_55109B8A0538__INCLUDED_)
#define AFX_SCENE_H__80F81C89_C5FE_40F0_8D8E_55109B8A0538__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\DD.h"
#include "..\include\DS.h"
#include <string>

class CScene  
{
protected:
	CDD* m_pDD;
	CDS* m_pDS;
	HWND m_hWnd;
	HINSTANCE m_hInstance;
public:	
	virtual bool Init(std::string strScenePath) = 0;
	virtual bool Draw() = 0;
	CScene();
	CScene(CDD* pDD, HWND hWnd, HINSTANCE hInstance);
	virtual ~CScene() = 0;
	bool PlayMusic();
	bool StopMusic();
	bool CheckAndLoop();
};

#endif // !defined(AFX_SCENE_H__80F81C89_C5FE_40F0_8D8E_55109B8A0538__INCLUDED_)
