// BattleScene.cpp: implementation of the CBattleScene class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\BattleScene.h"
#include <fstream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CBattleScene::CBattleScene(CDD* pDD, HWND hWnd, HINSTANCE hInstance)
	:CScene(pDD, hWnd, hInstance)
{
	m_iMainCharFrameIndex = 3;
	m_iDarkMagicFrameIndex = -1;
	m_iLightMagicFrameIndex = -1;

	m_iMainCharFrameCounter = 0;
	m_iDarkMagicFrameCounter = 0;
	m_iLightMagicFrameCounter = 0;

//	m_pDarkMagicPic = 0;
	m_pTileDarkMagicOp = 0;
//	m_pLightMagicPic = 0;
	m_pTileLightMagicOp = 0;
	m_pCursorPic = 0;
	m_pBackgroundPic = 0;

	m_pTileMainCharOp = 0;

	m_iBackgroundPicX = 0;
	m_iBackgroundPicY = 0;
	
	m_bMagic = false;
	m_bSetBkPic = false;
	m_bSetBoss = false;

	m_iCursorPos = 0;
}

CBattleScene::~CBattleScene()
{
//	if (m_MainCharPicInfo.getPicPtr())
//	{
//		delete m_MainCharPicInfo.getPicPtr(); 
//		m_MainCharPicInfo.setPicPtr(0);
//	}
	if ( m_pTileDarkMagicOp ) { delete m_pTileDarkMagicOp; m_pTileDarkMagicOp = 0; }	
	if ( m_pTileLightMagicOp ) { delete m_pTileLightMagicOp; m_pTileLightMagicOp = 0; }	
	if ( m_pCursorPic ) { delete m_pCursorPic; m_pCursorPic = 0; }
	if ( m_pBackgroundPic ) { delete m_pBackgroundPic; m_pBackgroundPic = 0; }
	if ( m_pTileMainCharOp ) { delete m_pTileMainCharOp; m_pTileMainCharOp = 0; }

	m_strBackgroundPicPath.clear();
}

bool CBattleScene::Draw()
{
	if (!m_bSetBkPic)
		return false;

	bool bRet;
	//RECT srcrt, destrt;
	/*
	destrt.left = 50;
	destrt.right = destrt.left + 200;
	destrt.top = 30;
	destrt.bottom = destrt.top + 150;
	bRet = m_pDD->FillWithColor( &destrt, RGB( 254, 251, 259 ) );
	if ( !bRet ) { return false; }
	*/

	bRet = DrawBackgroundPic();
	if ( !bRet ) { return false; }

	bRet = DrawMainChar();
	if ( !bRet ) { return false; }

	//Draw Monster Picture
	//{
		bRet = m_Monster.Draw(m_pDD);
		if ( !bRet ) { return false; }
	//}	

	bRet = DrawLightMagic();
	if ( !bRet ) { return false; }
	bRet = DrawDarkMagic();
	if ( !bRet ) { return false; }	

	//Draw text for user
	std::string strTemp = "The battle scene hasn't finished yet!\n";
	strTemp += "You can press Enter to return to the map scene.\n";
	strTemp += "You can use Up and Down arrow key for effect.";
	m_pDD->DrawText(strTemp,
		0, 0, RGB(255, 255, 255));

	return true;
}

bool CBattleScene::DrawBackgroundPic()
{
	RECT destrt;
	bool bRet;
	destrt.left = m_iBackgroundPicX;
	destrt.right = destrt.left + 320;
	destrt.top = m_iBackgroundPicY;
	destrt.bottom = destrt.top + 240;

	bRet = m_pDD->DrawPic(m_pBackgroundPic,
		&destrt, 0);
	if ( !bRet ) { return false; }
	return true;
}

bool CBattleScene::DrawMainChar()
{
	bool bRet;
	//Main character picture position calculation
	//{		
		bRet = m_pTileMainCharOp->setSrcXYFromID( m_iMainCharFrameIndex );
		if ( !bRet ) { return false; }
	//}

	//Main character animation frame index calculation
	//{
		if ( m_iMainCharFrameCounter - 1 > 0 )
		{
			m_iMainCharFrameCounter--;
			m_iMainCharFrameIndex++;
		}
		else
		{
			m_iMainCharFrameIndex = 3;
			m_iMainCharFrameCounter = -1;
			m_bMagic = false;
		}
	//}

	//Draw Main Character Picture
	//{
		if ( m_pTileMainCharOp )
		{
			bRet = m_pTileMainCharOp->Draw();
			if ( !bRet ) { return false; }
		}
	//}
	return true;
}

bool CBattleScene::DrawLightMagic()
{
	bool bRet;
	//Draw Light Magic Picture
	//{
		if ( !m_pTileLightMagicOp ) { return false; }
		if ( m_iLightMagicFrameIndex != -1 )
		{
			bRet = m_pTileLightMagicOp->setSrcXYFromID(m_iLightMagicFrameIndex);
			if ( !bRet ) { return false; }
			bRet = m_pTileLightMagicOp->Draw();
			if ( !bRet ) { return false; }
		}
	//}

	//Light Magic animation frame index calculation
	//{
		if ( m_iLightMagicFrameCounter - 1 > 0 )
		{
			m_iLightMagicFrameCounter--;
			m_iLightMagicFrameIndex ++;
		}
		else
		{
			m_iLightMagicFrameIndex = -1;
			m_iLightMagicFrameCounter = -1;
			m_bMagic = false;
		}
	//}
	
	return true;
}

bool CBattleScene::DrawDarkMagic()
{
	//Draw Dark Magic Picture
	//{
		bool bRet;
		if ( !m_pTileDarkMagicOp ) { return false; }
		if ( m_iDarkMagicFrameIndex != -1 )
		{
			bRet = m_pTileDarkMagicOp->setSrcXYFromID(m_iDarkMagicFrameIndex);
			if ( !bRet ) { return false; }
			bRet = m_pTileDarkMagicOp->Draw();
			if ( !bRet ) { return false; }
		}
	//}

	//Dark Magic animation frame index calculation
	//{
		if ( m_iDarkMagicFrameCounter - 1 > 0 )
		{
			m_iDarkMagicFrameCounter--;
			m_iDarkMagicFrameIndex ++;
		}
		else
		{
			m_iDarkMagicFrameIndex = -1;
			m_iDarkMagicFrameCounter = -1;
			m_bMagic = false;
		}
	//}
		return true;
}

bool CBattleScene::Init(std::string strScenePath)
{
	if ( m_pTileMainCharOp ) { return false; }
	if ( m_pTileDarkMagicOp ) { return false; }
	if ( m_pTileLightMagicOp ) { return false; }
	std::ifstream filestream;
	filestream.open(strScenePath.c_str());
	if ( !filestream.is_open() )
		return false;

	bool bRet;

	std::string strPath, strX, strY, strBgNum, strTemp,
		strName;
	
	//Load Main character picture in battle scene
	m_pTileMainCharOp = new CTileOp(m_pDD);
	if ( !m_pTileMainCharOp ) { return false; }
	getline(filestream, strPath); //Path
	bRet = m_pTileMainCharOp->Init(strPath);
	if ( !bRet ) { return false; }
	bRet = m_pTileMainCharOp->SetColorKey(RGB(32, 165, 0), RGB(32, 165, 0) );
	if ( !bRet ) { return false; }
	//Set Main Char Pic Dest X Y
	unsigned int iX, iY;
	getline(filestream, strX); //X coordinate
	iX = atoi(strX.c_str());
	getline(filestream, strY); //Y coordinate
	iY = atoi(strY.c_str());

	m_pTileMainCharOp->setDestXY(iX, iY);
	m_pTileMainCharOp->setSrcTileWidth(145);
	m_pTileMainCharOp->setSrcTileHeight(110);
	m_pTileMainCharOp->setDestTileWidth(145);
	m_pTileMainCharOp->setDestTileHeight(110);
	m_pTileMainCharOp->setNumTilePerRow(11);

	//Load Dark Magic picture
	//{
		getline(filestream, strPath);
		m_pTileDarkMagicOp = new CTileOp(m_pDD);
		bRet = m_pTileDarkMagicOp->Init(strPath);
		//bRet = m_pDD->CreatePic(strPath, &m_pDarkMagicPic);
		if ( !bRet ) { return false; }
		 m_pTileDarkMagicOp->setNumTilePerRow(5);
		if ( !bRet ) { return false; }

		m_pTileDarkMagicOp->setSrcTileWidth(96);
		m_pTileDarkMagicOp->setSrcTileHeight(96);
		m_pTileDarkMagicOp->setDestTileWidth(96);
		m_pTileDarkMagicOp->setDestTileHeight(96);
		m_pTileDarkMagicOp->setDestXY(450, 330);

		bRet = m_pTileDarkMagicOp->SetColorKey( RGB(45, 139, 89), RGB(45, 139, 89) );
		if ( !bRet ) { return false; }
	//}

	//Load Light Magic picture
	//{
		getline(filestream, strPath);
		m_pTileLightMagicOp = new CTileOp(m_pDD);
		bRet = m_pTileLightMagicOp->Init(strPath);
		//bRet = m_pDD->CreatePic(strPath, &m_pDarkMagicPic);
		if ( !bRet ) { return false; }
		 m_pTileLightMagicOp->setNumTilePerRow(5);
		if ( !bRet ) { return false; }

		m_pTileLightMagicOp->setSrcTileWidth(96);
		m_pTileLightMagicOp->setSrcTileHeight(96);
		m_pTileLightMagicOp->setDestTileWidth(96);
		m_pTileLightMagicOp->setDestTileHeight(96);
		m_pTileLightMagicOp->setDestXY(450, 330);

		bRet = m_pTileLightMagicOp->SetColorKey( RGB(45, 139, 89), RGB(45, 139, 89) );
		if ( !bRet ) { return false; }
	//}

	//Load Background number
	//{
	getline(filestream, strBgNum);
	int iBgNum = atoi(strBgNum.c_str());
	//}

	getline(filestream, strX);
	iX = atoi(strX.c_str());
	m_iBackgroundPicX = iX;
	getline(filestream, strY);
	iY = atoi(strY.c_str());
	m_iBackgroundPicY = iY;
	//Load Background picture
	//{
	for (int i=0; i<iBgNum; i++)
	{
		getline(filestream, strPath);
		m_strBackgroundPicPath.push_back(strPath);
	}	
	//}

	//Load Cursor picture
	//{
		getline(filestream, strPath); //Path
		bRet = m_pDD->CreatePic(strPath, &m_pCursorPic);
		if ( !bRet ) { return false; }
	//}
	
	unsigned int iMonNum;
	//Get Monster Number
	getline(filestream, strTemp);
	iMonNum = atoi(strTemp.c_str());

	std::vector<int> viMonsterX;
	std::vector<int> viMonsterY;
	std::vector<string> vstrMonsterPath;
	std::vector<string> vstrMonsterName;
	//Get all monster picture path
	for (i=0; i<iMonNum; i++)
	{
		getline(filestream, strX);
		iX = atoi(strX.c_str());
		viMonsterX.push_back(iX);

		getline(filestream, strY);
		iY = atoi(strY.c_str());
		viMonsterY.push_back(iY);

		getline(filestream, strName);
		vstrMonsterName.push_back(strName);

		getline(filestream, strPath);
		vstrMonsterPath.push_back(strPath);
	}

	std::string strBossPath, strBossName;
	int iBossX, iBossY;

	//Get Boss picture info
	getline(filestream, strX);
	iBossX = atoi(strX.c_str());
	getline(filestream, strY);
	iBossY = atoi(strY.c_str());
	getline(filestream, strBossName);
	getline(filestream, strBossPath);
	
	if ( !m_bSetBoss ) 
	{
		//Decide which monster
		int iMonsterRand = rand() % iMonNum;

		std::string strMonsterPath, strMonsterName;

		strMonsterPath = vstrMonsterPath[iMonsterRand];
		strMonsterName = vstrMonsterName[iMonsterRand];

		iX = viMonsterX[iMonsterRand];
		iY = viMonsterY[iMonsterRand];

		m_Monster.Init(m_pDD, strMonsterPath, strMonsterName,
			iX, iY);
	}
	else
	{
		//Set boss as monster
		m_Monster.Init(m_pDD, strBossPath, strBossName,
			iBossX, iBossY);
	}
	
	m_pDS->Create(m_hWnd, m_hInstance);
	std::string strBkMusicPath;
	m_pDS->LoadSound(strBkMusicPath.c_str());
	m_pDS->PlaySound();	
	
	filestream.close();
	return true;
}

void CBattleScene::LightMagic()
{
	if ( !m_bMagic )
	{
		if ( m_iLightMagicFrameCounter == -1 )
		{
			m_iMainCharFrameIndex = 0;
			m_iMainCharFrameCounter = 3;
			int iLightMagicType = rand() % 3;
			switch (iLightMagicType)
			{
			case 0:
				m_iLightMagicFrameCounter = 5;
				m_iLightMagicFrameIndex = 0;
				break;
			case 1:
				m_iLightMagicFrameCounter = 5;
				m_iLightMagicFrameIndex = 5;
				break;
			case 2:
				m_iLightMagicFrameCounter = 1;
				m_iLightMagicFrameIndex = 10;
				break;
			}
			PlaySound(".\\music\\l_saber.wav", 0, SND_FILENAME | SND_ASYNC); 
			m_bMagic = true;
		}
	}
}

void CBattleScene::DarkMagic()
{
	if ( !m_bMagic )
	{
		if ( m_iDarkMagicFrameCounter == -1 )
		{
			m_iMainCharFrameIndex = 3;
			m_iMainCharFrameCounter = 6;
			int iDarkMagicType = rand() % 2;
			switch (iDarkMagicType)
			{
			case 0:
				m_iDarkMagicFrameCounter = 7;
				m_iDarkMagicFrameIndex = 0;
				break;
			case 1:
				m_iDarkMagicFrameCounter = 4;
				m_iDarkMagicFrameIndex = 10;
				break;
			}
			PlaySound(".\\music\\cloak.wav", 0, SND_FILENAME | SND_ASYNC); 
			m_bMagic = true;
		}
	}
}

bool CBattleScene::setBackgroundPic(unsigned int iMapID)
{
	std::string strPath = m_strBackgroundPicPath[iMapID];
	bool bRet = m_pDD->CreatePic(strPath, &m_pBackgroundPic);
	if ( !bRet ) { return false; }
	m_bSetBkPic = true;
	return true;
}

void CBattleScene::moveCursorDown()
{

}

void CBattleScene::moveCursorUp()
{

}
