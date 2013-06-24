// DD.h: interface for the CDD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DD_H__FA89D3B9_2965_458E_A9F4_6867853F6A7B__INCLUDED_)
#define AFX_DD_H__FA89D3B9_2965_458E_A9F4_6867853F6A7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ddraw.h>
#include <string>
//#include <gdiplus.h>
using namespace std;
//using namespace Gdiplus;

#include "..\include\Pic.h"

class CDD  
{
	LPDIRECTDRAW7 m_lpDD;
	LPDIRECTDRAWSURFACE7 m_lpPrimarySurface, m_lpBackBuffer;
	LPDIRECTDRAWCLIPPER	m_lpClip;
	DWORD ConvertGDIColor( COLORREF dwGDIColor );
	unsigned int m_nScreenHeight;
	unsigned int m_nScreenWidth;
	HINSTANCE m_hInstance;
	HWND m_hWnd;
public:
	bool FillWithColor(RECT *pDestRt, DWORD dwColor);
	bool DrawFullPic(CPic *pPic, unsigned int nX, unsigned int nY);
//	bool CreatePicGdiplus(string strFileName, LPPic *ppPic);
//	bool CreatePicFromOwnFormat(string strFileName, LPPic *ppPic);
	bool DrawText(string strText, unsigned int nX, unsigned int nY,
				   DWORD dwTextColor);
	bool TransAlphaFast(CPic* pPic,
					   LONG lDestX, LONG lDestY,
					   RECT* pSrcRect, DWORD dwColorKey, WORD BPP);
	bool BltBackToPri();
	bool CreateWindowMode(HWND hWnd, HINSTANCE hInstance,
		unsigned int nScreenWidth, unsigned int nScreenHeight);
	bool FlipSurface();
	bool ClearBackBuffer();
	bool DrawPic(CPic* pPic, 
		LPRECT pDestRt, LPRECT pSrcRt);
	bool CreatePic(string strFileName, LPPic *ppPic);
	bool Create(HWND hWnd, HINSTANCE hInstance,
		unsigned int nScreenWidth, unsigned int nScreenHeight,
		unsigned int nBitPerPixel);
	void CleanUp();
	CDD();
	virtual ~CDD();
};

#endif // !defined(AFX_DD_H__FA89D3B9_2965_458E_A9F4_6867853F6A7B__INCLUDED_)
