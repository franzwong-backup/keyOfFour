// AlphaBlend.h: interface for the CAlphaBlend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALPHABLEND_H__14771F2C_EF83_4292_A7A8_B050A36342E8__INCLUDED_)
#define AFX_ALPHABLEND_H__14771F2C_EF83_4292_A7A8_B050A36342E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ddraw.h>

class CAlphaBlend  
{
public:
	CAlphaBlend();
	virtual ~CAlphaBlend();
	bool TransAlphaFast(LPDIRECTDRAWSURFACE7 srcSurface, LPDIRECTDRAWSURFACE7 destSurface, 
					   LONG lDestX, LONG lDestY, RECT *pSrcRect, DWORD dwColorKey, WORD BPP);
};

#endif // !defined(AFX_ALPHABLEND_H__14771F2C_EF83_4292_A7A8_B050A36342E8__INCLUDED_)
