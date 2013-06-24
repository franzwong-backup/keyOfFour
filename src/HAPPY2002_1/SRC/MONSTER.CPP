// Monster.cpp: implementation of the CMonster class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\Monster.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonster::CMonster()
{
	m_pMonsterPic = 0;
	m_iX = 0;
	m_iY = 0;
}

CMonster::~CMonster()
{
	CleanUp();
}

void CMonster::Operation()
{

}

bool CMonster::Init(CDD *pDD, 
					std::string strFilePath,
					std::string strMonsterName,
					unsigned int iX, unsigned int iY)
{
	bool bRet;
	bRet = pDD->CreatePic(strFilePath, &m_pMonsterPic);
	if ( !bRet ) { return false; }
	m_pMonsterPic->SetColorKey(RGB(255, 0, 0), RGB(255, 0, 0));
	m_strMonsterName = strMonsterName;
	m_iX = iX;
	m_iY = iY;
	return true;
}

bool CMonster::Draw(CDD *pDD)
{
	bool bRet;
	bRet = pDD->DrawFullPic(m_pMonsterPic, m_iX, m_iY);
	if ( !bRet ) { return false; }
	bRet = pDD->DrawText(m_strMonsterName, 30, 90, RGB(255, 255, 255));
	if ( !bRet ) { return false; }
	return true;
}

void CMonster::CleanUp()
{
	if ( m_pMonsterPic ) { delete m_pMonsterPic; m_pMonsterPic = 0; }
}
