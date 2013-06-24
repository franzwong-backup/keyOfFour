// Monster.h: interface for the CMonster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONSTER_H__31C8486A_263E_4220_989D_E08F54CCBE1E__INCLUDED_)
#define AFX_MONSTER_H__31C8486A_263E_4220_989D_E08F54CCBE1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\pic.h"
#include "..\include\picinfo.h"
#include "..\include\DD.h"
#include <string>

class CMonster  
{
	CPic* m_pMonsterPic;
	unsigned int m_iX;
	unsigned int m_iY;
	unsigned int m_nHP;
	unsigned int m_nFrameState;
	std::string m_strMonsterName;
public:
	void CleanUp();
	bool Draw(CDD* pDD);
	bool Init(CDD *pDD, 
		std::string strFilePath,
		std::string strMonsterName,
		unsigned int iX, unsigned int iY);
	void Operation();
	CMonster();
	virtual ~CMonster();	
};

#endif // !defined(AFX_MONSTER_H__31C8486A_263E_4220_989D_E08F54CCBE1E__INCLUDED_)
