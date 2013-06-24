// MenuScene.cpp: implementation of the CMenuScene class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\MenuScene.h"
#include <fstream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMenuScene::CMenuScene(CDD* pDD, HWND hWnd, HINSTANCE hInstance)
	:CScene(pDD, hWnd, hInstance)
{
	m_pMainTitlePic = 0;
	m_pOptionPic = 0;
	m_pCursorPic = 0;
	m_iCursorPos = 0;
	m_strAnvilSound = "";
	m_strBgMusicPath = "";
}

CMenuScene::~CMenuScene()
{
	m_pDD = 0;
	m_hWnd = 0;
	m_iCursorPos = 0;
	m_strAnvilSound = "";
	m_strBgMusicPath = "";
	if (m_pMainTitlePic) { delete m_pMainTitlePic; m_pMainTitlePic = 0; }
	if (m_pOptionPic) { delete m_pOptionPic; m_pOptionPic = 0; }
	if (m_pCursorPic) { delete m_pCursorPic; m_pCursorPic = 0; }
}

bool CMenuScene::Init(std::string strScenePath)
{
	bool bRet;
	if ( !m_pDD ) { return false; }
	std::ifstream filestream;
	filestream.open( strScenePath.c_str() );
	if ( !filestream.is_open() )
		return false;
	std::string strPath, strX, strY;

	//Get Main Title pic info
	std::getline(filestream, strPath);
	std::getline(filestream, strY);
	//Create Main Title
	bRet = m_pDD->CreatePic(strPath, &m_pMainTitlePic);
	if ( !bRet ) { return false; }
	m_MainTitleInfo.setPicInfo( ( 640 - m_pMainTitlePic->getWidth() ) / 2,
		atoi( strY.c_str() ),
		m_pMainTitlePic);

	//Get Option pic info
	std::getline(filestream, strPath);
	std::getline(filestream, strY);
	//Create Option
	bRet = m_pDD->CreatePic(strPath, &m_pOptionPic);
	if ( !bRet ) { return false; }
	m_OptionInfo.setPicInfo( ( 640 - m_pOptionPic->getWidth() ) / 2,
		atoi( strY.c_str() ),
		m_pOptionPic);

	//Get Cursor pic info
	std::getline(filestream, strPath);
	std::getline(filestream, strX);
	std::getline(filestream, strY);
	//Create Cursor
	bRet = m_pDD->CreatePic(strPath, &m_pCursorPic);
	if ( !bRet ) { return false; }
	m_CursorInfo.setPicInfo( atoi( strX.c_str() ),
		atoi( strY.c_str() ),
		m_pCursorPic);
	//Get Thunder Path
	std::getline(filestream, strPath);
	::PlaySound(strPath.c_str(), 0, SND_FILENAME | SND_ASYNC);

	//Get Anvil Sound Path
	std::getline(filestream, m_strAnvilSound);
	//Get Background Sound Path
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

bool CMenuScene::Draw()
{
	bool bRet;
	bRet = m_pDD->DrawFullPic( m_MainTitleInfo.getPicPtr(),
		m_MainTitleInfo.getX(), m_MainTitleInfo.getY() );
	if ( !bRet ) { return false; }
	bRet = m_pDD->DrawFullPic( m_OptionInfo.getPicPtr(),
		m_OptionInfo.getX(), m_OptionInfo.getY() );
	if ( !bRet ) { return false; }
	bRet = m_pDD->DrawFullPic( m_CursorInfo.getPicPtr(),
		m_CursorInfo.getX(), m_CursorInfo.getY()+m_iCursorPos*80 );
	if ( !bRet ) { return false; }
	return true;
}

bool CMenuScene::PlayAnvilSound()
{
	::PlaySound(m_strAnvilSound.c_str(), 0, SND_FILENAME | SND_ASYNC);
	return true;
}


void CMenuScene::moveCursorUp()
{
	if ( m_iCursorPos > 0 )
	{
		m_iCursorPos--;
	}
}
void CMenuScene::moveCursorDown()
{
	if ( m_iCursorPos < MENUSCENE_MENUITEMNUM - 1 )
	{
		m_iCursorPos++;
	}
}