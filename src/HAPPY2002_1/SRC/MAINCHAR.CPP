// MainChar.cpp: implementation of the CMainChar class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\MainChar.h"
#include "..\include\MapScene.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMainChar::CMainChar()
{
	m_nX = 1;
	m_nY = 9;
	m_nHP = 0;
	m_nMP = 0;
	m_strName = "Master Glid";
	m_pCurrentMap = 0;
	m_nKeyNum = 0;
	m_iFaceDirection = UP;
	m_bWalk = false;
}

CMainChar::~CMainChar()
{
	m_pCurrentMap = 0;
}

void CMainChar::AddMP(int nAddMP) 
{
	if (nAddMP >= 0)
	{
		if ( m_nMP+nAddMP <= m_nFullMP )
			m_nMP += nAddMP;
	}
}
void CMainChar::AddHP(int nAddHP)
{
	if (nAddHP >= 0)
	{
		if ( m_nHP+nAddHP <= m_nFullHP )
			m_nHP += nAddHP;
	}
}

void CMainChar::AddKeyNum()
{
	if ( m_nKeyNum + 1 <= 4 )
	{
		m_nKeyNum++;
	}
}

void CMainChar::MinusMP(int nMinusMP)
{
	if (nMinusMP >= 0)
	{
		if ( m_nMP-nMinusMP >=0 )
			m_nMP -= nMinusMP;
	}
}

void CMainChar::MinusHP(int nMinusHP)
{
	if (nMinusHP >= 0)
	{
		if ( m_nHP-nMinusHP >= 0 )
			m_nHP -= nMinusHP;
	}
}

void CMainChar::setFullHP(int nFullHP)
{ 
	if ( nFullHP >= 0 ) 
		m_nFullHP = nFullHP; 
}

void CMainChar::setHP(int nHP) 
{ 
	if ( ( nHP <= m_nFullHP ) && ( nHP >= 0 ) )
		m_nHP = nHP; 
}

void CMainChar::setFullMP(int nFullMP)
{
	if ( nFullMP >= 0 )
		m_nFullMP = nFullMP; 
}

void CMainChar::setMP(int nMP)
{ 
	if ( ( nMP <= m_nFullMP )  && ( nMP >= 0 ) )
		m_nMP = nMP;
}

/*
bool CMainChar::Draw(CDD *pDD)
{


	return true;
}

bool CMainChar::InitMainChar(CDD *pDD, std::string strFileName,
							 CMap* pCurrentMap)
{
	bool bRet;
	bRet = pDD->CreatePic(strFileName, &m_pMainCharPic);
	if (!bRet) { return false; }
	bRet = m_pMainCharPic->SetColorKey( RGB(32,156,0), RGB(32,156,0) );
	if (!bRet) { return false; }
	m_pCurrentMap = pCurrentMap;
	return true;
}
*/
void CMainChar::MoveUp(CMapScene* pMapScene)
{
	if ( m_nY > 0 )
	{
		if ( m_pCurrentMap->m_iWalkableMap[m_nY-1][m_nX] == 1 )
		{
			if ( !m_bWalk )
			{
				m_nY -= 1;
				m_bWalk = true;
				m_iFaceDirection = UP;
			}
		}
	}
	else
	{
		CMap* pMap;
		pMap = m_pCurrentMap->getUpMap();
		if ( pMap )
		{
			m_pCurrentMap = pMap;
			m_nY = 10;
			pMapScene->setCurrentMap(m_pCurrentMap);
		}
	}	
}

void CMainChar::MoveDown(CMapScene* pMapScene)
{
	if ( m_nY < 10 )
	{
		if ( m_pCurrentMap->m_iWalkableMap[m_nY+1][m_nX] == 1)
		{
			if ( !m_bWalk )
			{
				m_nY += 1;
				m_bWalk = true;
				m_iFaceDirection = DOWN;
			}
		}
	}
	else
	{
		CMap* pMap;
		pMap = m_pCurrentMap->getDownMap();
		if ( pMap )
		{
			m_pCurrentMap = pMap;
			m_nY = 0;
			pMapScene->setCurrentMap(m_pCurrentMap);
		}
	}	
}

void CMainChar::MoveLeft(CMapScene* pMapScene)
{
	if ( m_nX > 0 )
	{
		if ( m_pCurrentMap->m_iWalkableMap[m_nY][m_nX-1] == 1 )
		{
			if ( !m_bWalk )
			{
				m_nX -= 1;
				m_bWalk = true;
				m_iFaceDirection = LEFT;
			}
		}
	}
	else
	{
		CMap* pMap;
		pMap = m_pCurrentMap->getLeftMap();
		if (pMap)
		{
			m_pCurrentMap = pMap;
			m_nX = 14;
			pMapScene->setCurrentMap(m_pCurrentMap);
		}
	}	
}

void CMainChar::MoveRight(CMapScene* pMapScene)
{
	if ( m_nX < 14 )
	{
		if ( m_pCurrentMap->m_iWalkableMap[m_nY][m_nX+1] == 1 )
		{
			if ( !m_bWalk )
			{
				m_nX += 1;
				m_bWalk = true;
				m_iFaceDirection = RIGHT;
			}
		}
	}
	else
	{
		CMap* pMap;
		pMap = m_pCurrentMap->getRightMap();
		if ( pMap )
		{
			m_pCurrentMap = pMap;
			m_nX = 0;
			pMapScene->setCurrentMap(m_pCurrentMap);
		}
	}	
}
/*
void CMainChar::PushMap(CMap *pMap)
{
	m_vpMap.push_back(pMap);
}
*/