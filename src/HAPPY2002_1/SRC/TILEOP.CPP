// TileOp.cpp: implementation of the CTileOp class.
//
//////////////////////////////////////////////////////////////////////

#include "../include/TileOp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTileOp::CTileOp()
{
	m_pDD = 0;
	m_pPic = 0;

	m_iNumTilePerRow = 0;

	m_iSrcTileHeight = 0;
	m_iSrcTileWidth = 0;

	m_bSetNumTilePerRow = false;
	m_bSetDestTileWidth = false;
	m_bSetDestTileHeight = false;	
	m_bSetSrcTileWidth = false;
	m_bSetSrcTileHeight = false;
}

CTileOp::CTileOp(CDD* pDD)
{
	m_pDD = pDD;
	m_pPic = 0;

	m_iNumTilePerRow = 0;
	
	m_iSrcTileHeight = 0;
	m_iSrcTileWidth = 0;

	m_bSetNumTilePerRow = false;
	m_bSetDestTileWidth = false;
	m_bSetDestTileHeight = false;	
	m_bSetSrcTileWidth = false;
	m_bSetSrcTileHeight = false;
}

CTileOp::~CTileOp()
{
	m_pDD = 0;
	if ( m_pPic ) { delete m_pPic; m_pPic = 0; }
}

bool CTileOp::setSrcXYFromID(unsigned int iID)
{
	if ( ( m_bSetNumTilePerRow ) && ( m_bSetSrcTileWidth ) && ( m_bSetSrcTileHeight ) )
	{
		m_iSrcX = ( iID % m_iNumTilePerRow ) * m_iSrcTileWidth;
		m_iSrcY = ( iID / m_iNumTilePerRow ) * m_iSrcTileHeight;
	}
	else
		return false;
	return true;
}

bool CTileOp::Init(std::string strPicPath)
{
	bool bRet;
	bRet = m_pDD->CreatePic(strPicPath, &m_pPic);
	if ( !bRet ) { return false; }
	return true;
}

bool CTileOp::Draw()
{
	RECT srcrt, destrt;
	if ( !m_pDD ) { return false; }
	if ( !( ( m_bSetSrcTileWidth ) && ( m_bSetSrcTileHeight ) ) ) { return false; }
	if ( !( ( m_bSetDestTileWidth ) && ( m_bSetDestTileHeight ) ) ) { return false; }

	srcrt.left = m_iSrcX;
	srcrt.right = srcrt.left + m_iSrcTileWidth;
	srcrt.top = m_iSrcY;
	srcrt.bottom = srcrt.top + m_iSrcTileHeight ;

	destrt.left = m_iDestX;
	destrt.right = destrt.left + m_iDestTileWidth;
	destrt.top = m_iDestY;
	destrt.bottom = destrt.top + m_iDestTileHeight;

	bool bRet;
	bRet = m_pDD->DrawPic(m_pPic, &destrt, &srcrt);

	if ( !bRet ) { return false; }
	return true;
}

bool CTileOp::SetColorKey(DWORD dwHighColorKey, DWORD dwLowColorKey)
{
	bool bRet;
	bRet = m_pPic->SetColorKey(dwHighColorKey, dwLowColorKey);
	if ( !bRet ) { return false; }
	return true;
}