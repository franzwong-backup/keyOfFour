// OpeningScene.h: interface for the COpeningScene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENINGSCENE_H__34111CE7_2892_4ADC_95FA_FD8FB9D14FDD__INCLUDED_)
#define AFX_OPENINGSCENE_H__34111CE7_2892_4ADC_95FA_FD8FB9D14FDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\Scene.h"
#include "..\include\Pic.h"
#include "..\include\PicInfo.h"
#include "..\include\DS.h"
#include <string>

class COpeningScene : public CScene  
{
	std::string m_strOpeningText;
	unsigned int m_iFrameNum;
public:
	bool Init(std::string strScenePath);
	COpeningScene(CDD* pDD, HWND hWnd, HINSTANCE hInstance);
	virtual ~COpeningScene();
	bool Draw();
	bool Operate();
	inline void addFrameNum() { if ( m_iFrameNum < 146 ) m_iFrameNum += 5; }
	inline unsigned int getFrameNum() { return m_iFrameNum; }
};

#endif // !defined(AFX_OPENINGSCENE_H__34111CE7_2892_4ADC_95FA_FD8FB9D14FDD__INCLUDED_)
