// TileOp.h: interface for the CTileOp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILEOP_H__DBC1A158_C9BF_48B7_AB70_59453EE459DC__INCLUDED_)
#define AFX_TILEOP_H__DBC1A158_C9BF_48B7_AB70_59453EE459DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DD.h"
#include "Pic.h"
#include <string>

class CTileOp 
{
	CPic* m_pPic;
	CDD* m_pDD;

	unsigned int m_iNumTilePerRow;
	bool m_bSetNumTilePerRow;

	unsigned int m_iSrcTileWidth;
	bool m_bSetSrcTileWidth;
	unsigned int m_iSrcTileHeight;
	bool m_bSetSrcTileHeight;

	unsigned int m_iDestTileWidth;
	bool m_bSetDestTileWidth;
	unsigned int m_iDestTileHeight;
	bool m_bSetDestTileHeight;

	unsigned int m_iSrcX;
	unsigned int m_iSrcY;

	unsigned int m_iDestX;
	unsigned int m_iDestY;

public:
	CTileOp();
	CTileOp(CDD* pDD);
	virtual ~CTileOp();

	void setNumTilePerRow(unsigned int iNumTilePerRow) 
	{ m_iNumTilePerRow = iNumTilePerRow; m_bSetNumTilePerRow = true; }
	void setSrcTileWidth(unsigned int iSrcTileWidth) 
	{ m_iSrcTileWidth = iSrcTileWidth; m_bSetSrcTileWidth = true;}
	void setSrcTileHeight(unsigned int iSrcTileHeight) 
	{ m_iSrcTileHeight = iSrcTileHeight; m_bSetSrcTileHeight = true;}

	void setDestTileWidth(unsigned int iDestTileWidth) 
	{ m_iDestTileWidth = iDestTileWidth; m_bSetDestTileWidth = true; }
	void setDestTileHeight(unsigned int iDestTileHeight) 
	{ m_iDestTileHeight = iDestTileHeight; m_bSetDestTileHeight = true; }

	void setSrcX(unsigned int iSrcX) { m_iSrcX = iSrcX; }
	void setSrcY(unsigned int iSrcY) { m_iSrcY = iSrcY; }
	void setSrcXY(unsigned int iSrcX, unsigned int iSrcY) 
	{ m_iSrcX = iSrcX; m_iSrcY = iSrcY; }

	void setDestX(unsigned int iDestX) { m_iDestX = iDestX; }
	void setDestY(unsigned int iDestY) { m_iDestY = iDestY; }
	void setDestXY(unsigned int iDestX, unsigned int iDestY) 
	{ m_iDestX = iDestX; m_iDestY = iDestY; }

	bool setSrcXYFromID(unsigned int iID);

	bool Init(std::string strPicPath);
	bool Draw();
	bool SetColorKey(DWORD dwHighColorKey, DWORD dwLowColorKey);
};

#endif // !defined(AFX_TILEOP_H__DBC1A158_C9BF_48B7_AB70_59453EE459DC__INCLUDED_)
