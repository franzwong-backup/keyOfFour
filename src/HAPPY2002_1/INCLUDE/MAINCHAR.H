// MainChar.h: interface for the CMainChar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINCHAR_H__45CA656E_8B82_4230_9D97_C079C2F61A2E__INCLUDED_)
#define AFX_MAINCHAR_H__45CA656E_8B82_4230_9D97_C079C2F61A2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\Pic.h"
#include "..\include\DD.h"
#include "..\include\Map.h"
#include <string>
#include <vector>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class CMapScene;

class CMainChar  
{
	unsigned int m_nX;
	unsigned int m_nY;

	unsigned int m_nMP;
	unsigned int m_nHP;

	unsigned int m_nFullHP;
	unsigned int m_nFullMP;

	unsigned int m_nLevel;
	unsigned int m_nExpLeft;

	unsigned int m_nKeyNum;

	CMap *m_pCurrentMap;

	std::string m_strName;

	unsigned int m_iFaceDirection;
	bool m_bWalk;

public:
	//Constructor and destructor
	CMainChar();
	virtual ~CMainChar();

	//Movement on map
	void MoveRight(CMapScene* pMapScene);
	void MoveLeft(CMapScene* pMapScene);
	void MoveDown(CMapScene* pMapScene);
	void MoveUp(CMapScene* pMapScene);

	//Set Table
	void setFullHP(int nFullHP);
	void setHP(int nHP);
	void setFullMP(int nFullMP);
	void setMP(int nMP);
	void setCurrentMap(CMap* pCurrentMap) { m_pCurrentMap = pCurrentMap; }
	void setWalk(bool bWalk) { m_bWalk = bWalk; }
	
	void AddMP(int nAddMP);
	void AddHP(int nAddHP);
	void AddKeyNum();
	void MinusMP(int nMinusMP);
	void MinusHP(int nMinusHP);

	//Get Table
	unsigned int getFullHP() { return m_nFullHP; }
	unsigned int getFullMP() { return m_nFullMP; }
	unsigned int getHP() { return m_nHP; }	
	unsigned int getMP() { return m_nMP; }
	unsigned int getX() { return m_nX; }
	unsigned int getY() { return m_nY; }
	unsigned int getFaceDirection() { return m_iFaceDirection; }
	bool getWalk() { return m_bWalk; }
};

#endif // !defined(AFX_MAINCHAR_H__45CA656E_8B82_4230_9D97_C079C2F61A2E__INCLUDED_)
