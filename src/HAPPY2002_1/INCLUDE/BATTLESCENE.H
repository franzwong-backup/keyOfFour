// BattleScene.h: interface for the CBattleScene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BATTLESCENE_H__A5C71803_882E_476A_A008_084F737C282A__INCLUDED_)
#define AFX_BATTLESCENE_H__A5C71803_882E_476A_A008_084F737C282A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)

#include "..\include\Scene.h"
#include "..\include\Pic.h"
#include "..\include\TileOp.h"
#include "..\include\Monster.h"
#include <string>
#include <vector>

#define MAINCAHR 1
#define MONSTER 2

#define BATTLESCENE_MENUITEMNUM 5

class CBattleScene : public CScene  
{
	CPic* m_pBackgroundPic;
	std::vector<string> m_strBackgroundPicPath;

	//CPic* m_pDarkMagicPic;
	CTileOp* m_pTileDarkMagicOp;
	CTileOp* m_pTileLightMagicOp;
	//CPic* m_pLightMagicPic;
	CPic* m_pCursorPic;

	//CPicInfo m_MainCharPicInfo;
	CTileOp* m_pTileMainCharOp;

	unsigned int m_iMainCharFrameIndex;
	unsigned int m_iDarkMagicFrameIndex;
	unsigned int m_iLightMagicFrameIndex;

	int m_iMainCharFrameCounter;
	int m_iDarkMagicFrameCounter;
	int m_iLightMagicFrameCounter;

	bool m_bMagic;
	bool m_bPlayTurn;
	unsigned int m_iCursorPos;

	unsigned int m_iBackgroundPicX;
	unsigned int m_iBackgroundPicY;

	bool m_bSetBkPic;
	bool m_bSetBoss;

	CMonster m_Monster;
	
	bool DrawBackgroundPic();
	bool DrawMainChar();
	bool DrawLightMagic();
	bool DrawDarkMagic();
public:
	CBattleScene(CDD* pDD, HWND hWnd, HINSTANCE hInstance);
	virtual ~CBattleScene();

	void moveCursorUp();
	void moveCursorDown();	

	bool Init(std::string strScenePath);
	bool Draw();

	bool setBackgroundPic(unsigned int iMapID);
	void setBoss() { m_bSetBoss = true; }

	void DarkMagic();
	void LightMagic();
};

#endif // !defined(AFX_BATTLESCENE_H__A5C71803_882E_476A_A008_084F737C282A__INCLUDED_)
