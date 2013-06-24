// PicInfo.cpp: implementation of the CPicInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\PicInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPicInfo::CPicInfo()
{
	m_pPic = 0;
	m_nX = 0;
	m_nY = 0;
}

CPicInfo::~CPicInfo()
{
	m_pPic = 0;
	m_nX = 0;
	m_nY = 0;
}

void CPicInfo::setPicInfo(unsigned int nX, unsigned int nY, CPic* pPic)
{
	m_nX = nX;
	m_nY = nY;
	m_pPic = pPic;
}
