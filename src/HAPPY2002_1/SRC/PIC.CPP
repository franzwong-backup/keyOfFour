// Pic.cpp: implementation of the CPic class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\Pic.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPic::CPic(unsigned int nWidth, unsigned int nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_bColorKey = false;
}

CPic::~CPic()
{
	CleanUp();
}

HRESULT CPic::CreateSurface( LPDIRECTDRAW7 lpDD, DDSURFACEDESC2 *ddsd,
							unsigned int nWidth, unsigned int nHeight)
{
	HRESULT hRet = lpDD->CreateSurface( ddsd, &m_lpds, NULL );
	if ( SUCCEEDED(hRet) ) { m_nWidth = nWidth; m_nHeight = nHeight; }
	return hRet;
}

void CPic::CleanUp()
{
	if ( m_lpds ) { m_lpds->Release(); m_lpds = 0; }
	m_nWidth = 0;
	m_nHeight = 0;
}

LPDIRECTDRAWSURFACE7 CPic::getSurface() { return m_lpds; }

unsigned int CPic::getWidth() {	return m_nWidth; }
unsigned int CPic::getHeight() { return m_nHeight; }

/*
void CPic::setHeight(unsigned int nHeight)
{ m_nHeight = nHeight; }

void CPic::setWidth(unsigned int nWidth)
{ m_nWidth = nWidth; }
*/

bool CPic::SetColorKey(DWORD dwHighColorKey, DWORD dwLowColorKey)
{
	DDCOLORKEY ddck;
    ddck.dwColorSpaceLowValue  = ConvertGDIColor(dwLowColorKey);
    ddck.dwColorSpaceHighValue = ConvertGDIColor(dwHighColorKey);
    HRESULT hRet;
	if ( ddck.dwColorSpaceHighValue == ddck.dwColorSpaceLowValue )
		hRet = m_lpds->SetColorKey( DDCKEY_SRCBLT, &ddck );
	else
	{
		hRet = m_lpds->SetColorKey( DDCKEY_SRCBLT | DDCKEY_COLORSPACE, &ddck );
	}
	if ( FAILED(hRet) ) { return false; }
	m_bColorKey = true;
	return true;
}

DWORD CPic::ConvertGDIColor( COLORREF dwGDIColor )
{
    if( m_lpds == NULL )
	    return 0x00000000;

    COLORREF       rgbT;
    HDC            hdc;
    DWORD          dw = CLR_INVALID;
    DDSURFACEDESC2 ddsd;
    HRESULT        hr;

    //  Use GDI SetPixel to color match for us
    if( dwGDIColor != CLR_INVALID && m_lpds->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);     // Save current pixel value
        SetPixel(hdc, 0, 0, dwGDIColor);       // Set our value
        m_lpds->ReleaseDC(hdc);
    }

    // Now lock the surface so we can read back the converted color
    ddsd.dwSize = sizeof(ddsd);
    hr = m_lpds->Lock( NULL, &ddsd, DDLOCK_WAIT, NULL );
    if( hr == DD_OK)
    {
        dw = *(DWORD *) ddsd.lpSurface; 
        if( ddsd.ddpfPixelFormat.dwRGBBitCount < 32 ) // Mask it to bpp
            dw &= ( 1 << ddsd.ddpfPixelFormat.dwRGBBitCount ) - 1;  
        m_lpds->Unlock(NULL);
    }

    //  Now put the color that was there back.
    if( dwGDIColor != CLR_INVALID && m_lpds->GetDC(&hdc) == DD_OK )
    {
        SetPixel( hdc, 0, 0, rgbT );
        m_lpds->ReleaseDC(hdc);
    }
    
    return dw;    
}
