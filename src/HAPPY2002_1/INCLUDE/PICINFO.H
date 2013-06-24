// PicInfo.h: interface for the CPicInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICINFO_H__0652B75D_44F0_4E32_996C_C4263D2C2F0B__INCLUDED_)
#define AFX_PICINFO_H__0652B75D_44F0_4E32_996C_C4263D2C2F0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\Pic.h"

class CPicInfo  
{
	unsigned int m_nX;
	unsigned int m_nY;
	CPic* m_pPic;
public:
	void setPicInfo(unsigned int nX, unsigned int nY, CPic* pPic);
	void setX(unsigned int nX) { m_nX = nX; }
	void setY(unsigned int nY) { m_nY = nY; }
	void setPicPtr(CPic* pPic) { m_pPic = pPic; }

	CPic* getPicPtr() { return m_pPic; }
	unsigned int getX() { return m_nX; }
	unsigned int getY() { return m_nY; }

	CPicInfo();
	virtual ~CPicInfo();
};

#endif // !defined(AFX_PICINFO_H__0652B75D_44F0_4E32_996C_C4263D2C2F0B__INCLUDED_)
