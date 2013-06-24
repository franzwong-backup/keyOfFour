// DD.cpp: implementation of the CDD class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\DD.h"
#include "..\include\alphablend.h"
#include <algorithm>
#include <fstream>
#include <mmsystem.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDD::CDD()
{
	m_lpDD = 0;
	m_lpClip = 0;
	m_lpPrimarySurface = 0;
	m_lpBackBuffer = 0;
	m_hWnd = 0;
	m_hInstance = 0;
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
}

CDD::~CDD()
{
	CleanUp();
}

void CDD::CleanUp()
{
	//clean up clipper
	if ( m_lpClip ) { m_lpClip->Release(); m_lpClip = 0; }
	//clean up back buffer
	if ( m_lpBackBuffer ) { m_lpBackBuffer->Release(); m_lpBackBuffer = 0; }
	//clean up primary surface
	if ( m_lpPrimarySurface ) { m_lpPrimarySurface->Release(); m_lpPrimarySurface = 0; }
	//clean up direct draw object
	if ( m_lpDD ) { m_lpDD->Release(); m_lpDD = 0; }	
	//Reset the handle of window and instance
	m_hWnd = 0;
	m_hInstance = 0;
	//Reset the dimension of the window
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
}

bool CDD::Create(HWND hWnd, HINSTANCE hInstance,
				 unsigned int nScreenWidth, unsigned int nScreenHeight,
				 unsigned int nBitPerPixel)
{
	//If directdraw object is already created
	if (m_lpDD) { return false; }

	//create the directdraw object
	HRESULT hRet = DirectDrawCreateEx( NULL, (VOID**)&m_lpDD, IID_IDirectDraw7, NULL );
	if ( FAILED(hRet) )	{ return false; }

	hRet = m_lpDD->SetCooperativeLevel( hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN );
	if ( FAILED(hRet) ) { return false; }

	hRet = m_lpDD->SetDisplayMode( nScreenWidth, nScreenHeight,
		nBitPerPixel, 0, 0 );
	if ( FAILED(hRet) ) { return false; }

	//Create Clipper
	hRet = m_lpDD->CreateClipper(0,&m_lpClip,0);
	if ( FAILED(hRet) )	{ return false; }
	hRet = m_lpClip->SetHWnd(0,hWnd);
	if ( FAILED(hRet) )	{ return false; }

	// Create the primary surface with one back buffer.
	DDSURFACEDESC2 ddsd;
	ZeroMemory( &ddsd, sizeof(ddsd) );
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP |
						  DDSCAPS_COMPLEX;
	ddsd.dwBackBufferCount = 1;
	hRet = m_lpDD->CreateSurface( &ddsd, &m_lpPrimarySurface, NULL );
	if ( FAILED(hRet) ) { return false; }

	m_lpPrimarySurface->SetClipper(m_lpClip);
	if ( FAILED(hRet) )	{ return false; }

	//Create the back buffer
	DDSCAPS2 ddscaps;
	ZeroMemory( &ddscaps, sizeof(ddscaps) );
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	hRet = m_lpPrimarySurface->GetAttachedSurface( &ddscaps, &m_lpBackBuffer );
	if ( FAILED(hRet) ) { return false; }

	m_lpBackBuffer->SetClipper(m_lpClip);
	if ( FAILED(hRet) )	{ return false; }

	//Give the handle of window and instance to CDD
	m_hWnd = hWnd;
	m_hInstance = hInstance;

	//Give the dimension of the window to CDD
	m_nScreenWidth = nScreenWidth;
	m_nScreenHeight = nScreenHeight;
	
	//success
	return true;
}

bool CDD::CreateWindowMode(HWND hWnd, HINSTANCE hInstance,
				 unsigned int nScreenWidth, unsigned int nScreenHeight)
{
	if ( m_lpDD ) { return false; }
	
	//Create Direct Draw Object
	DDSURFACEDESC2 ddsd;
	HRESULT hRet = DirectDrawCreateEx(NULL,(LPVOID *)&m_lpDD,IID_IDirectDraw7,NULL);
	if ( FAILED(hRet) )	{ return false;	}
	hRet = m_lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
	if ( FAILED(hRet) )	{ return false; }

	//Create Primary Surface
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	hRet = m_lpDD->CreateSurface(&ddsd,&m_lpPrimarySurface,NULL);
	if ( FAILED(hRet) )	{ return false; }

	//Create Clipper
	hRet = m_lpDD->CreateClipper(NULL,&m_lpClip,NULL);
	if ( FAILED(hRet) )	{ return false; }
	hRet = m_lpClip->SetHWnd(0,hWnd);
	if ( FAILED(hRet) )	{ return false; }
	hRet = m_lpPrimarySurface->SetClipper(m_lpClip);
	if ( FAILED(hRet) )	{ return false; }

	//Create Back Buffer
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.dwWidth = nScreenWidth;
	ddsd.dwHeight = nScreenHeight;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	hRet = m_lpDD->CreateSurface(&ddsd,&m_lpBackBuffer,NULL);
	if ( FAILED(hRet) )	{ return false; }
	hRet = m_lpBackBuffer->SetClipper(m_lpClip);
	if ( FAILED(hRet) )	{ return false; }

	//Send the information of the window to the CDD
	m_hInstance = hInstance;
	m_hWnd = hWnd;
	m_nScreenHeight = nScreenHeight;
	m_nScreenWidth = nScreenWidth;

	return true;
}

bool CDD::CreatePic(string strFileName, LPPic *ppPic)
{
	if ( !m_hInstance ) { return false; }
	if ( !m_lpDD ) { return false; }
	if ( *ppPic ) { return false; }

	//Load the bitmap to HBITMAP from file
	HBITMAP hbm = NULL; 
	hbm = (HBITMAP) LoadImage(m_hInstance, strFileName.c_str(), 
		IMAGE_BITMAP,0,0, 
		LR_DEFAULTCOLOR|LR_DEFAULTSIZE|LR_LOADFROMFILE); 
	if ( !hbm ) { return false; }	//Error occur

	//Get the info of the bitmap
	BITMAP bmp;
	GetObject(hbm, sizeof(bmp),&bmp);

	//Define surface info
	HRESULT	hRet;
    DDSURFACEDESC2 ddsd;
    ZeroMemory( &ddsd, sizeof( ddsd ) );
    ddsd.dwSize         = sizeof( ddsd );
    ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT; 
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth        = bmp.bmWidth;
    ddsd.dwHeight       = bmp.bmHeight;

	//Create CPic object and surface
	*ppPic = new CPic( bmp.bmWidth, bmp.bmHeight );
	hRet = (*ppPic)->CreateSurface(m_lpDD, &ddsd, bmp.bmWidth, bmp.bmHeight);
	if ( FAILED(hRet) ) { delete *ppPic; *ppPic = 0; DeleteObject(hbm); return false; }

	HDC hdc = 0;
	hRet = (*ppPic)->getSurface()->GetDC(&hdc);
	if ( FAILED(hRet) )
	{
		delete *ppPic;
		*ppPic = 0;
		DeleteObject(hbm);
		return false;
	}
	HDC dcBitmap = 0;
	dcBitmap = CreateCompatibleDC(hdc);
	if ( !dcBitmap )
	{ 
		(*ppPic)->getSurface()->ReleaseDC(hdc);
		DeleteDC(dcBitmap);
		delete *ppPic;
		*ppPic = 0;
		DeleteObject(hbm);
		return false;
	}

	SelectObject(dcBitmap, hbm); 
 
	//Draw it on the direct draw surface
	BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, dcBitmap, 0, 0, SRCCOPY);

	hRet = (*ppPic)->getSurface()->ReleaseDC(hdc);
	DeleteObject(hbm);
	DeleteDC(dcBitmap);	

	return true;
}
/*
bool CDD::CreatePicGdiplus(string strFileName, LPPic *ppPic)
{
	if ( !m_hInstance ) { return false; }
	if ( !m_lpDD ) { return false; }
	if ( *ppPic ) { return false; }
	
	wstring widestrFileName(strFileName.length(), L' ');
	copy(strFileName.begin(), strFileName.end(), widestrFileName.begin());

	Bitmap *pBmp = new Bitmap( widestrFileName.c_str() );

	//Define surface info
	HRESULT	hRet;
    DDSURFACEDESC2 ddsd;
    ZeroMemory( &ddsd, sizeof( ddsd ) );
    ddsd.dwSize         = sizeof( ddsd );
    ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth        = pBmp->GetWidth();
    ddsd.dwHeight       = pBmp->GetHeight();

	*ppPic = new CPic( pBmp->GetWidth(), pBmp->GetHeight() );
	hRet = (*ppPic)->CreateSurface(m_lpDD, &ddsd, pBmp->GetWidth(), pBmp->GetHeight());
	if ( FAILED(hRet) ) { delete pBmp; delete *ppPic; *ppPic = 0; return false; }

	HDC hdc = 0;
	hRet = (*ppPic)->getSurface()->GetDC(&hdc);
	if ( FAILED(hRet) ) { delete pBmp; delete *ppPic; *ppPic = 0; return false; }

	Graphics *pGra = new Graphics(hdc);
	pGra->DrawImage(pBmp, 0, 0);

	delete pGra;
	pGra = 0;

	(*ppPic)->getSurface()->ReleaseDC(hdc);

	delete pBmp;
	pBmp = 0;

	return true;
}
*/
bool CDD::DrawPic(CPic *pPic, 
					LPRECT pDestRt, LPRECT pSrcRt)
{
	if ( !pPic ) { return false; }

	HRESULT hRet;

	if (pPic->IsColorKeyed())
		hRet = m_lpBackBuffer->Blt(pDestRt, pPic->getSurface(), pSrcRt, DDBLT_KEYSRC, 0);
	else
		hRet = m_lpBackBuffer->Blt(pDestRt, pPic->getSurface(), pSrcRt, 0, 0);

	if ( FAILED(hRet) ) 
	{ 
		if ( hRet == DDERR_SURFACELOST )
		{
			hRet = m_lpBackBuffer->Restore();
			if ( FAILED(hRet) ) { return false; }
			hRet = pPic->getSurface()->Restore();
			if ( FAILED(hRet) ) { return false; }

			if (pPic->IsColorKeyed())
			{ hRet = m_lpBackBuffer->Blt(pDestRt,
				pPic->getSurface(), pSrcRt, DDBLT_KEYSRC, 0); }
			else
			{ hRet = m_lpBackBuffer->Blt(pDestRt,
				pPic->getSurface(), pSrcRt, 0, 0); }
			if ( FAILED(hRet) ) { return false; }
		}
		else
			return false; 
	}
	return true;	
}

bool CDD::DrawFullPic(CPic *pPic, unsigned int nX, unsigned int nY)
{
	RECT destrt;
	destrt.top = nY;
	destrt.left = nX;
	destrt.bottom = nY+pPic->getHeight();//-1;
	destrt.right = nX+pPic->getWidth();//-1;

	bool bRet = DrawPic(pPic, &destrt, 0);
	return bRet;
}

bool CDD::ClearBackBuffer()
{
	DDBLTFX ddbltfx;
	ZeroMemory( &ddbltfx, sizeof(ddbltfx) );
	ddbltfx.dwSize      = sizeof(ddbltfx);
    ddbltfx.dwFillColor = 0;
	HRESULT hRet = m_lpBackBuffer->Blt( NULL, NULL, NULL, DDBLT_COLORFILL, &ddbltfx );
	if ( FAILED(hRet) ) 
	{ 
		if ( hRet == DDERR_SURFACELOST )
		{
			hRet = m_lpBackBuffer->Restore();
			if ( FAILED(hRet) ) { return false; }
			hRet = m_lpBackBuffer->Blt( NULL, NULL, NULL, DDBLT_COLORFILL, &ddbltfx );
			if ( FAILED(hRet) ) { return false; }
		}
		else
			return false; 
	}
	return true;
}

bool CDD::FlipSurface()
{
	HRESULT hRet = m_lpPrimarySurface->Flip(0, 0);
	if ( FAILED(hRet) ) { return false; }
	return true;
}

bool CDD::BltBackToPri()
{
	HRESULT hRet = m_lpPrimarySurface->Blt(0, m_lpBackBuffer, 0, 0, 0);
	if ( FAILED(hRet) )	{ return false; }
	return true;
}

bool CDD::DrawText(string strText, unsigned int nX, unsigned int nY,
				   DWORD dwTextColor)
{
	HDC hdc = 0;
	HRESULT hRet = m_lpBackBuffer->GetDC(&hdc);
	if ( FAILED(hRet) ) { return false; }
	//TextOut(hdc, nX, nY, strText.c_str(), strText.size());
	RECT srcrt;
	srcrt.left = nX;
	srcrt.top = nY;
	srcrt.right = srcrt.left + 600;
	srcrt.bottom = srcrt.top + 300;
	//::SetBkColor(hdc, dwBgColor);
	::SetBkMode(hdc, TRANSPARENT);
	::SetTextColor(hdc, dwTextColor);
	::DrawText(hdc, strText.c_str(), strText.length(), &srcrt, DT_LEFT);
	hRet = m_lpBackBuffer->ReleaseDC(hdc);
	if ( FAILED(hRet) ) { return false; }
	return true;
}
/*
bool CDD::CreatePicFromOwnFormat(string strFileName, LPPic *ppPic)
{
	if ( !m_hInstance ) { return false; }
	if ( !m_lpDD ) { return false; }
	if ( *ppPic ) { return false; }
	
	std::ifstream filestream;
	filestream.open(strFileName.c_str());
	if ( !filestream.is_open() )
		return false;

	int iWidth, iHeight;
	filestream.read((char*)&iWidth, sizeof(int));
	filestream.read((char*)&iHeight, sizeof(int));

	//Define surface info
	HRESULT	hRet;
    DDSURFACEDESC2 ddsd;
    ZeroMemory( &ddsd, sizeof( ddsd ) );
    ddsd.dwSize         = sizeof( ddsd );
    ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth        = iWidth;
    ddsd.dwHeight       = iHeight;

	*ppPic = new CPic( iWidth, iHeight );
	hRet = (*ppPic)->CreateSurface(m_lpDD, &ddsd, iWidth, iHeight);
	if ( FAILED(hRet) ) { delete *ppPic; *ppPic = 0; return false; }

	Gdiplus::Bitmap *pBmp = Bitmap::FromDirectDrawSurface7((*ppPic)->getSurface());
	BYTE byteR, byteG, byteB;
	for (int i=0; i<iHeight; i++)
	{
		for (int j=0; j<iWidth; j++)
		{
			filestream.read((char*)&byteR, sizeof(BYTE));
			filestream.read((char*)&byteG, sizeof(BYTE));
			filestream.read((char*)&byteB, sizeof(BYTE));
			Color myColor(255, byteR, byteG, byteB);
			pBmp->SetPixel(j, i, myColor);
		}
	}	
	delete pBmp;
	pBmp = 0;

	filestream.close();

	return true;
}
*/

bool CDD::FillWithColor(RECT *pDestRt, DWORD dwColor)
{
	DDBLTFX ddbltfx;
	ZeroMemory( &ddbltfx, sizeof(ddbltfx) );
	ddbltfx.dwSize      = sizeof(ddbltfx);
    ddbltfx.dwFillColor = ConvertGDIColor(dwColor);
	HRESULT hRet = m_lpBackBuffer->Blt( pDestRt, NULL, NULL, DDBLT_COLORFILL, &ddbltfx );
	if ( FAILED(hRet) ) { return false; }
	return true;
}

DWORD CDD::ConvertGDIColor( COLORREF dwGDIColor )
{
    if( m_lpBackBuffer == NULL )
	    return 0x00000000;

    COLORREF       rgbT;
    HDC            hdc;
    DWORD          dw = CLR_INVALID;
    DDSURFACEDESC2 ddsd;
    HRESULT        hr;

    //  Use GDI SetPixel to color match for us
    if( dwGDIColor != CLR_INVALID && m_lpBackBuffer->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);     // Save current pixel value
        SetPixel(hdc, 0, 0, dwGDIColor);       // Set our value
        m_lpBackBuffer->ReleaseDC(hdc);
    }

    // Now lock the surface so we can read back the converted color
    ddsd.dwSize = sizeof(ddsd);
    hr = m_lpBackBuffer->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
    if( hr == DD_OK)
    {
        dw = *(DWORD *) ddsd.lpSurface; 
        if( ddsd.ddpfPixelFormat.dwRGBBitCount < 32 ) // Mask it to bpp
            dw &= ( 1 << ddsd.ddpfPixelFormat.dwRGBBitCount ) - 1;  
        m_lpBackBuffer->Unlock(NULL);
    }

    //  Now put the color that was there back.
    if( dwGDIColor != CLR_INVALID && m_lpBackBuffer->GetDC(&hdc) == DD_OK )
    {
        SetPixel( hdc, 0, 0, rgbT );
        m_lpBackBuffer->ReleaseDC(hdc);
    }
    
    return dw;    
}
/*
bool CDD::TransAlphaFast(CPic* pPic,
					   LONG lDestX, LONG lDestY,
					   RECT* pSrcRect, DWORD dwColorKey, WORD BPP)
{
	bool bRet;
	CAlphaBlend alphablend;
	bRet = alphablend.TransAlphaFast(pPic->getSurface(), m_lpBackBuffer, lDestX, lDestY,
		pSrcRect, dwColorKey, BPP);
	if ( !bRet ) { return false; }
	return true;
}*/