// MapScene.h: interface for the CMapScene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPSCENE_H__3A253A4C_BBC7_4835_A5AD_2CEEE8744359__INCLUDED_)
#define AFX_MAPSCENE_H__3A253A4C_BBC7_4835_A5AD_2CEEE8744359__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\Scene.h"
#include "..\include\Map.h"
#include "..\include\MainChar.h"
#include "..\include\TileOp.h"
#include <string>
#include <vector>

#define MAPNUM 4

class CMapScene : public CScene  
{
//	CMap m_map[MAPNUM];
	CMap* m_pMap;
	CMap *m_pCurrentMap;
	unsigned int m_iMapNum;

	CTileOp* m_pTileRoadOp;
	CPic *m_pBackgroundPic;
	CTileOp* m_pTileMainCharOp;

	CMainChar* m_pMainChar;
	unsigned int m_nMainCharFrameState;
	unsigned int m_nMainCharFrameState2;

	std::string m_strTypeSoundPath;

	int m_iTextEffect;
public:
	//Constructor and destructor
	CMapScene(CDD* pDD, HWND hWnd, HINSTANCE hInstance);
	virtual ~CMapScene();

	//Basic operation
	bool Init(std::string strScenePath);
	bool Draw();
	void CalculateTextEffect();

	//Get Table
	CMap* getCurrentMap() { return m_pCurrentMap; }
	CMap* getMapByID(unsigned int iMapID)
	{
		if ( ( iMapID >= 0 ) && ( iMapID <= m_iMapNum ) )
			return (m_pMap+iMapID);
		else
			return 0;
	}

	//Set Table
	void setCurrentMap(CMap* pCurrentMap)
	{
		m_pCurrentMap = pCurrentMap;
		CalculateTextEffect();
	}	
	void setMainCharPtr(CMainChar* pMainChar) { m_pMainChar = pMainChar; }
	void setMainCharUpFrame();
	void setMainCharDownFrame();
	void setMainCharLeftFrame();
	void setMainCharRightFrame();
};

#endif // !defined(AFX_MAPSCENE_H__3A253A4C_BBC7_4835_A5AD_2CEEE8744359__INCLUDED_)
