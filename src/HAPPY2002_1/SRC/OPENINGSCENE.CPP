// OpeningScene.cpp: implementation of the COpeningScene class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\OpeningScene.h"
#include <fstream>
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpeningScene::COpeningScene(CDD* pDD, HWND hWnd, HINSTANCE hInstance)
	:CScene(pDD, hWnd, hInstance)
{
	m_strOpeningText = "";
	m_iFrameNum = 10;	
}

COpeningScene::~COpeningScene()
{
	m_pDD = 0;
	m_hWnd = 0;
}

bool COpeningScene::Init(std::string strScenePath)
{
	std::ifstream filestream;
	filestream.open(strScenePath.c_str());
	if ( !filestream.is_open() )
		return false;
	std::string strTextPath, strTemp;
	//Load the path of the opening text file
	std::getline(filestream, strTextPath);
	//Load the path of the background music
	std::string strBgMusicPath;
	std::getline(filestream, strBgMusicPath);
	//Init CDS and play background music
	m_pDS->Create(m_hWnd, m_hInstance);
	m_pDS->LoadSound(strBgMusicPath.c_str());
	m_pDS->PlaySound();
	filestream.close();

	filestream.clear();
	//Load the text of the opening
	filestream.open(strTextPath.c_str());
	if ( !filestream.is_open() )
		return false;
	for (int i=0; i<7; i++)
	{
		std::getline(filestream, strTemp);
		strTemp += "\n";
		m_strOpeningText += strTemp;
	}
	filestream.close();

	return true;
}

bool COpeningScene::Draw()
{
	bool bRet;
	//Draw opening text ( story text )
	bRet = m_pDD->DrawText(m_strOpeningText, 
		115, (  240 - m_iFrameNum ) * 2 ,
		RGB(255, 255, 255));
	if ( !bRet ) { return false; }
	
	std::string strCaption = "";
	strCaption += "Press Enter or left mouse button to skip.\n";
	strCaption += "Demo 5";
	//Draw text for user
	bRet = m_pDD->DrawText(strCaption,
		0, 0, RGB(255, 255, 255));
	if ( !bRet ) { return false; }
	return true;
}

bool COpeningScene::Operate()
{
	if (m_iFrameNum < 150)
		m_iFrameNum++;
	return true;
}