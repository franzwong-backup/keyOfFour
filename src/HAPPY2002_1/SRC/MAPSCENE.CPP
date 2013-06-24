// MapScene.cpp: implementation of the CMapScene class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\MapScene.h"
#include <fstream>

#define FRAMEPERTILE 3

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapScene::CMapScene(CDD* pDD, HWND hWnd, HINSTANCE hInstance)
	:CScene(pDD, hWnd, hInstance)
{
	m_pTileRoadOp = 0;
	m_pCurrentMap = 0;
	m_pBackgroundPic = 0;
	m_pTileMainCharOp = 0;
	m_pMainChar = 0;
	m_strTypeSoundPath = "";
	m_nMainCharFrameState = 1;
	m_iTextEffect = 0;
	m_iMapNum = -1;
	m_pMap = 0;
	m_nMainCharFrameState2 = 1;	
}

CMapScene::~CMapScene()
{
	m_hWnd = 0;
	m_pDD = 0;
	m_pCurrentMap = 0;
	m_pMainChar = 0;
	m_strTypeSoundPath = "";
	if ( m_pMap ) { delete [] m_pMap; m_pMap = 0; }
	if ( m_pTileMainCharOp ) { delete m_pTileMainCharOp; m_pTileMainCharOp = 0; }
	if ( m_pTileRoadOp ) { delete m_pTileRoadOp; m_pTileRoadOp = 0; }
	if ( m_pBackgroundPic ) { delete m_pBackgroundPic; m_pBackgroundPic = 0; }
}

bool CMapScene::Init(std::string strScenePath)
{
	if ( !m_pDD ) { return false; }
	if ( m_pTileRoadOp ) { return false; }
	if ( m_pTileMainCharOp ) { return false; }
	if ( m_pBackgroundPic ) { return false; }

	bool bRet;
	std::ifstream filestream;
	filestream.open( strScenePath.c_str() );
	if ( !filestream.is_open() )
		return false;

	std::string strPath, strTemp;

	std::getline(filestream, strTemp);
	m_iMapNum = atoi(strTemp.c_str());
	m_pMap = new CMap[m_iMapNum];
	//Read Map File
	for (int i=0; i<m_iMapNum; i++)
	{
		std::getline(filestream, strPath);
		(m_pMap+i)->ReadMapFile(strPath, m_pMap);		
	}

	//Get the road picture path
	std::getline(filestream, strPath);
	//Create Road
	m_pTileRoadOp = new CTileOp(m_pDD);
	bRet = m_pTileRoadOp->Init(strPath);
	if ( !bRet ) { return false; }
	m_pTileRoadOp->setSrcTileWidth(32);
	m_pTileRoadOp->setSrcTileHeight(32);
	m_pTileRoadOp->setDestTileWidth(32);
	m_pTileRoadOp->setDestTileHeight(32);
	m_pTileRoadOp->setNumTilePerRow(8);

	//Get the background picture path
	std::getline(filestream, strPath);
	//Create background picture
	bRet = m_pDD->CreatePic(strPath, &m_pBackgroundPic);
	if ( !bRet ) { return false; }

	//Get the main char picture path
	std::getline(filestream, strPath);
	//Create Main Char
	m_pTileMainCharOp = new CTileOp(m_pDD);
	bRet = m_pTileMainCharOp->Init(strPath);
	if ( !bRet ) { return false; }
	m_pTileMainCharOp->setSrcTileWidth(24);
	m_pTileMainCharOp->setSrcTileHeight(32);
	m_pTileMainCharOp->setDestTileWidth(24);
	m_pTileMainCharOp->setDestTileHeight(32);
	m_pTileMainCharOp->setNumTilePerRow(3);
	bRet = m_pTileMainCharOp->SetColorKey(RGB(32, 156, 0), RGB(32, 156, 0));
	if ( !bRet ) { return false; }

	//Get the type sound path
	std::getline(filestream, m_strTypeSoundPath);	

	//Get the mp3 path
	std::string strBgMusicPath;
	std::getline(filestream, strBgMusicPath);
	bRet = m_pDS->Create(m_hWnd, m_hInstance);
	if ( !bRet ) { return false; }
	bRet = m_pDS->LoadSound(strBgMusicPath.c_str());
	if ( !bRet ) { return false; }
	bRet = m_pDS->PlaySound();
	if ( !bRet ) { return false; }

	filestream.close();	

	return true;
}

bool CMapScene::Draw()
{
	int iIndex;
	bool bRet;
	//Draw background
	for (int i=0; i<8; i++)
	{
		bRet = m_pDD->DrawFullPic(m_pBackgroundPic, i*83, 0);
		if ( !bRet ) { return false; }
	}
	for (i=0; i<8; i++)
	{
		bRet = m_pDD->DrawFullPic(m_pBackgroundPic, i*83, 294);
		if ( !bRet ) { return false; }
	}
	bRet = m_pDD->DrawFullPic(m_pBackgroundPic, 0, 147);
	if ( !bRet ) { return false; }
	for (i=0; i<2; i++)
	{
		bRet = m_pDD->DrawFullPic(m_pBackgroundPic, (6+i)*83, 147);
		if ( !bRet ) { return false; }
	}
	for (i=0; i<8; i++)
	{
		bRet = m_pDD->DrawFullPic(m_pBackgroundPic, i*83, 441);
		if ( !bRet ) { return false; }
	}
	std::string strMapName = m_pCurrentMap->getMapName();
	if (m_iTextEffect <=0 )
	{
		bRet = m_pDD->DrawText(strMapName,
			30, 30, RGB(255,255,255));
		if ( !bRet ) { return false; }
	}
	else
	{
		std::string strSubName;
		int iTextLength = strMapName.length();
		strSubName = strMapName.substr(0, iTextLength - m_iTextEffect);
		bRet = m_pDD->DrawText(strSubName,
			30, 30, RGB(255,255,255));
		::PlaySound(m_strTypeSoundPath.c_str(), 0, SND_FILENAME | SND_ASYNC); 
		if ( !bRet ) { return false; }
		m_iTextEffect--;
	}	

	//Draw Map
	if (m_pCurrentMap)
	{
		for (int i=0; i<MAP_HEIGHT; i++)
		{
			for (int j=0; j<MAP_WIDTH; j++)
			{
				iIndex = m_pCurrentMap->m_iMap[i][j];
				bRet = m_pTileRoadOp->setSrcXYFromID(iIndex);
				if ( !bRet ) { return false; }

				m_pTileRoadOp->setDestX(j * 32 + 80);
				m_pTileRoadOp->setDestY(i * 32 + 64);

				bRet = m_pTileRoadOp->Draw();
				if ( !bRet ) { return false; }
			}
		}
	}
	else
		return false;


	if (m_pMainChar->getWalk())
	{
		switch (m_pMainChar->getFaceDirection())
		{
		case UP:
			setMainCharUpFrame();
			break;
		case DOWN:
			setMainCharDownFrame();
			break;
		case LEFT:
			setMainCharLeftFrame();
			break;
		case RIGHT:
			setMainCharRightFrame();
			break;
		}
	}

	//Draw Main Character
	if ( ( m_nMainCharFrameState >= 0 ) && ( m_nMainCharFrameState <= 11) )
	{
		m_pTileMainCharOp->setSrcXYFromID(m_nMainCharFrameState);
	}

	if (m_pMainChar->getWalk())
	{
		switch (m_pMainChar->getFaceDirection())
		{
		case UP:
			{
				m_pTileMainCharOp->setDestX( m_pMainChar->getX() * 32 + 80 + 4);
				m_pTileMainCharOp->setDestY( m_pMainChar->getY() * 32 + 
					( ( FRAMEPERTILE - m_nMainCharFrameState2 ) * 32 / FRAMEPERTILE ) 
					+ 64);
			}break;
		case DOWN:
			{
				m_pTileMainCharOp->setDestX(m_pMainChar->getX() * 32 + 80 + 4);
				m_pTileMainCharOp->setDestY(m_pMainChar->getY() * 32 - 
					( ( FRAMEPERTILE - m_nMainCharFrameState2 ) * 32 / FRAMEPERTILE ) 
					+ 64);
			}break;
		case LEFT:
			{
				m_pTileMainCharOp->setDestX(m_pMainChar->getX() * 32 + 
					( ( FRAMEPERTILE - m_nMainCharFrameState2 ) * 32 / FRAMEPERTILE ) 
					+ 80 + 4);
				m_pTileMainCharOp->setDestY(m_pMainChar->getY() * 32 + 64);
			}break;
		case RIGHT:
			{
				m_pTileMainCharOp->setDestX(m_pMainChar->getX() * 32 - 
					( ( FRAMEPERTILE - m_nMainCharFrameState2 ) * 32 / FRAMEPERTILE ) 
					+ 80+ 4);
				m_pTileMainCharOp->setDestY(m_pMainChar->getY() * 32 + 64);
			}break;
		}
	}
	else
	{
		m_pTileMainCharOp->setDestX(m_pMainChar->getX() * 32 + 80 + 4);
		m_pTileMainCharOp->setDestY(m_pMainChar->getY() * 32 + 64);
	}

	bRet = m_pTileMainCharOp->Draw();
	if ( !bRet ) { return false; }

	if ( (m_nMainCharFrameState2 < FRAMEPERTILE) && ( m_nMainCharFrameState2 != 0 ) )
	{
		if (m_pMainChar->getWalk())
		{
			m_nMainCharFrameState2++;
		}
	}
	else
	{
		m_pMainChar->setWalk(false);
		m_nMainCharFrameState2 = 1;
	}

	return true;
}

void CMapScene::setMainCharUpFrame()
{
	if ( ( m_nMainCharFrameState >= 0 ) && ( m_nMainCharFrameState <= 2) )
	{
		if (m_nMainCharFrameState == 2)
			m_nMainCharFrameState = 0;
		else
			m_nMainCharFrameState ++;
	}
	else
		m_nMainCharFrameState = 0;
}

void CMapScene::setMainCharDownFrame()
{
	if ( ( m_nMainCharFrameState >= 6) && ( m_nMainCharFrameState <= 8) )
	{
		if (m_nMainCharFrameState == 8)
			m_nMainCharFrameState = 6;
		else
			m_nMainCharFrameState++;
	}
	else
		m_nMainCharFrameState = 6;
}

void CMapScene::setMainCharLeftFrame()
{
	if ( ( m_nMainCharFrameState >= 9) && ( m_nMainCharFrameState <= 11) )
	{
		if (m_nMainCharFrameState == 11)
			m_nMainCharFrameState = 9;
		else
			m_nMainCharFrameState++;
	}
	else
		m_nMainCharFrameState = 9;
}

void CMapScene::setMainCharRightFrame()
{
	if ( ( m_nMainCharFrameState >= 3) && ( m_nMainCharFrameState <= 5) )
	{
		if (m_nMainCharFrameState == 5)
			m_nMainCharFrameState = 3;
		else
			m_nMainCharFrameState++;
	}
	else
		m_nMainCharFrameState = 3;		
}

void CMapScene::CalculateTextEffect()
{
	std::string strMapName;
	strMapName = m_pCurrentMap->getMapName();
	m_iTextEffect = strMapName.length();
}