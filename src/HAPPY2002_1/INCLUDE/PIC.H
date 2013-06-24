// Pic.h: interface for the CPic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIC_H__07A1C6FD_52A0_4EC2_9F16_AEDF0879FCEB__INCLUDED_)
#define AFX_PIC_H__07A1C6FD_52A0_4EC2_9F16_AEDF0879FCEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ddraw.h>

class CPic  
{
	unsigned int m_nHeight;
	unsigned int m_nWidth;
	LPDIRECTDRAWSURFACE7 m_lpds;
	DWORD ConvertGDIColor( COLORREF dwGDIColor );
	bool m_bColorKey;
public:
	bool SetColorKey(DWORD dwHighColorKey, DWORD dwLowColorKey);
//	void setWidth(unsigned int nWidth);
//	void setHeight(unsigned int nHeight);
	unsigned int getHeight();
	unsigned int getWidth();
	bool IsColorKeyed() { return m_bColorKey; }
	LPDIRECTDRAWSURFACE7 getSurface();
	void CleanUp();
	HRESULT CreateSurface(LPDIRECTDRAW7 lpDD, DDSURFACEDESC2* ddsd,
		unsigned int nWidth, unsigned int nHeight);
	CPic(unsigned int nWidth, unsigned int nHeight);
	virtual ~CPic();
};

typedef CPic* LPPic;

#endif // !defined(AFX_PIC_H__07A1C6FD_52A0_4EC2_9F16_AEDF0879FCEB__INCLUDED_)
