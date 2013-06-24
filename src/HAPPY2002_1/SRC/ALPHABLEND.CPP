// AlphaBlend.cpp: implementation of the CAlphaBlend class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\alphablend.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlphaBlend::CAlphaBlend()
{

}

CAlphaBlend::~CAlphaBlend()
{

}

bool CAlphaBlend::TransAlphaFast(LPDIRECTDRAWSURFACE7 srcSurface, LPDIRECTDRAWSURFACE7 destSurface, 
					   LONG lDestX, LONG lDestY, RECT *pSrcRect, DWORD dwColorKey, WORD BPP)
{
    int register i,j;
	int height,width;
    BYTE* lpSprite;
    BYTE* lpDest;
    LONG dPitch, SpritePitch;
    DWORD sColorKey;
    DWORD sTemp,dTemp;
    WORD sbuf,dbuf;
    DWORD Result;
	BOOL oddWidth = FALSE;
	DDSURFACEDESC2 srcDDSD, destDDSD;

    // Set height and width of SPRITE
    height = pSrcRect->bottom - pSrcRect->top;
    width  = pSrcRect->right - pSrcRect->left;

    // Lock down both surfaces for read and write
	ZeroMemory(&srcDDSD, sizeof(srcDDSD));
	srcDDSD.dwSize = sizeof(srcDDSD);
	srcSurface->Lock(NULL, &srcDDSD, DDLOCK_WAIT, NULL);
    
	ZeroMemory(&destDDSD, sizeof(destDDSD));
	destDDSD.dwSize = sizeof(destDDSD);
	destSurface->Lock(NULL, &destDDSD, DDLOCK_WAIT, NULL);

    // Set the pitch for both surfaces
    SpritePitch = srcDDSD.lPitch;
    dPitch      = destDDSD.lPitch;

    // Initialize the pointers to the upper left hand corner of the surface
    lpSprite = (BYTE*)srcDDSD.lpSurface;
    lpDest   = (BYTE*)destDDSD.lpSurface;

	// Get the color key for sprite surface
	sColorKey = dwColorKey;

	// Start RGB Format switch statement
	switch(BPP)
	{
	case 8:
		// IMHO paletized modes are a thing of the past please feel free to 
		// implement this if you so desire.
		break;

	case 15:  ////////////////////////////////////////////////////////////////////////
		      //
		      //  WARNING!!!: I do not have a video card that uses the 5-5-5 format 
		      //              this barnch of code has not be tested.
		      //
		      ////////////////////////////////////////////////////////////////////////

		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (pSrcRect->top * SpritePitch) + (pSrcRect->left * 2);
		lpDest   += (lDestY * dPitch) + (lDestX * 2);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (2 * width));
		dbuf = (WORD)(dPitch - (2 * width));

		// Is the Sprite width odd or even?
		if (width % 2 == 1)
		{
			oddWidth = TRUE;
			width = (width - 1) / 2; //div by 2, processing 2 pixels at a time.
		}
		else
			width = width / 2;  //div by 2, processing 2 pixels at a time.


		i = height;
		do
		{
			if (oddWidth)
			{
				sTemp = *((WORD*)lpSprite);

				if (sTemp != sColorKey)
				{
					dTemp = *((WORD*)lpDest);
					*((WORD*)lpDest) = (WORD)(((sTemp & 0x7BDE) >> 1) + ((dTemp & 0x7BDE) >> 1));
				}

				lpDest   += 2;
				lpSprite += 2;
			}

			j = width;
			do
			{
				sTemp  = *((DWORD*)lpSprite);
				dTemp  = *((DWORD*)lpDest);
				Result = dTemp;

				if ((sTemp & 0xFFFF) != sColorKey)
				{
					Result &= 0xFFFF0000;
					Result |= ((sTemp & 0x7BDE) >> 1) + ((dTemp & 0x7BDE) >> 1);
				}
				if ((sTemp >> 16) != sColorKey)
				{
					Result &= 0xFFFF;
					Result |= ((sTemp & 0x7BDE0000) >> 1) + ((dTemp & 0x7BDE0000) >> 1);
				}

				*((DWORD*)lpDest) = Result;
				lpDest   += 4;
				lpSprite += 4;
			}while (--j > 0);
			lpDest   += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);

		break;

	case 16:

		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (pSrcRect->top * SpritePitch) + (pSrcRect->left * 2);
		lpDest   += (lDestY * dPitch) + (lDestX * 2);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (2 * width));
		dbuf = (WORD)(dPitch - (2 * width));

		// Is the Sprite width odd or even?
		if (width % 2 == 1)
		{
			oddWidth = TRUE;
			width = (width - 1) / 2; //div by 2, processing 2 pixels at a time.
		}
		else
			width = width / 2;  //div by 2, processing 2 pixels at a time.

		i = height;
		do
		{
			if (oddWidth)
			{
				sTemp = *((WORD*)lpSprite);

				if (sTemp != sColorKey)
				{
					dTemp = *((WORD*)lpDest);
					*((WORD*)lpDest) = (WORD)(((sTemp & 0xF7DE) >> 1) + ((dTemp & 0xF7DE) >> 1));
				}

				lpDest   += 2;
				lpSprite += 2;
			}

			j = width;
			do
			{
				sTemp  = *((DWORD*)lpSprite);
				dTemp  = *((DWORD*)lpDest);
				Result = dTemp;

				if ((sTemp & 0xFFFF) != sColorKey)
				{
					Result &= 0xFFFF0000;
					Result |= ((sTemp & 0xF7DE) >> 1) + ((dTemp & 0xF7DE) >> 1);
				}
				if ((sTemp >> 16) != sColorKey)
				{
					Result &= 0xFFFF;
					Result |= ((sTemp & 0xF7DE0000) >> 1) + ((dTemp & 0xF7DE0000) >> 1);
				}

				*((DWORD*)lpDest) = Result;
				lpDest   += 4;
				lpSprite += 4;

			}while (--j > 0);
			lpDest += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);
		break;

	case 24:  ////////////////////////////////////////////////////////////////////////
		      //
		      //  WARNING!!!: I do not have a video card capable of 24bit rendering 
		      //              this barnch of code has not be tested.
		      //
		      ////////////////////////////////////////////////////////////////////////

		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (pSrcRect->top * SpritePitch) + (pSrcRect->left * 3);
		lpDest   += (lDestY * dPitch) + (lDestX * 3);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (3 * width));
		dbuf = (WORD)(dPitch - (3 * width));

		i = height;
		do
		{
			j = width;
			do
			{
				sTemp = *((DWORD*)lpSprite);

				if ((sTemp &= 0xFFFFFF) != sColorKey)
				{
					dTemp  = *((DWORD*)lpDest);
					Result = ((sTemp & 0xFEFEFE) >> 1) + ((dTemp & 0xFEFEFE) >> 1);

					*((WORD*)lpDest) = (WORD)(Result & 0xFFFF);
					lpDest += 2;
					*lpDest = (BYTE)(Result >> 16);
					lpDest++;
				}
				else
				{
					lpDest += 3;
				}

				lpSprite += 3;

			}while (--j > 0);
			lpDest += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);
		break;

	case 32:
		// Initialize the pointers to the first pixel in the rectangle
		lpSprite += (pSrcRect->top * SpritePitch) + (pSrcRect->left * 4);
		lpDest   += (lDestY * dPitch) + (lDestX * 4);

		// Set the horizontal padding
		sbuf = (WORD)(SpritePitch - (4 * width));
		dbuf = (WORD)(dPitch - (4 * width));

		i = height;
		do
		{
			j = width;
			do
			{
				sTemp = *((DWORD*)lpSprite);

				if ((sTemp &= 0xFFFFFF) != sColorKey)
				{
					dTemp  = *((DWORD*)lpDest);
					Result = ((sTemp & 0xFEFEFE) >> 1) + ((dTemp & 0xFEFEFE) >> 1);

					*((WORD*)lpDest) = (WORD)(Result & 0xFFFF);
					lpDest += 2;
					*lpDest = (BYTE)(Result >> 16);
					lpDest += 2;
				}
				else
				{
					lpDest += 4;
				}

				lpSprite += 4;

			}while (--j > 0);
			lpDest += dbuf;
			lpSprite += sbuf;

		}while (--i > 0);
		break;
	} // End RGB Format switch statement


    srcSurface->Unlock(NULL);
    destSurface->Unlock(NULL);

	return DD_OK;
}