// MenuScene.h: interface for the CMenuScene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENUSCENE_H__52CA4F6F_B217_4DA5_A219_99918E09FCB8__INCLUDED_)
#define AFX_MENUSCENE_H__52CA4F6F_B217_4DA5_A219_99918E09FCB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\Scene.h"
#include "..\include\Pic.h"
#include "..\include\PicInfo.h"
#include "..\include\DS.h"
#include <string>

#define MENUSCENE_MENUITEMNUM 2

class CMenuScene : public CScene  
{
	CPic* m_pMainTitlePic;
	CPic* m_pOptionPic;
	CPic* m_pCursorPic;
	CPicInfo m_MainTitleInfo;
	CPicInfo m_OptionInfo;
	CPicInfo m_CursorInfo;
	std::string m_strAnvilSound;
	std::string m_strBgMusicPath;
	unsigned int m_iCursorPos;
public:
	CMenuScene(CDD* pDD, HWND hWnd, HINSTANCE hInstance);
	virtual ~CMenuScene();
	bool Init(std::string strScenePath);
	bool Draw();

	void moveCursorUp();
	void moveCursorDown();

	bool PlayAnvilSound();

	unsigned int getCursorPos() { return m_iCursorPos; }
};

#endif // !defined(AFX_MENUSCENE_H__52CA4F6F_B217_4DA5_A219_99918E09FCB8__INCLUDED_)
