// Map.cpp: implementation of the CMap class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "..\include\Map.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap::CMap()
{
	ZeroMemory(m_iMap, sizeof(int)*MAP_WIDTH*MAP_HEIGHT);
	ZeroMemory(m_iWalkableMap, sizeof(int)*MAP_WIDTH*MAP_HEIGHT);
	m_pLeftMap = 0;
	m_pRightMap = 0;
	m_pUpMap = 0;
	m_pDownMap = 0;
	m_strMapName = "";
}

CMap::~CMap()
{
	CleanUp();
}

void CMap::CleanUp()
{
	ZeroMemory(m_iMap, sizeof(int)*MAP_WIDTH*MAP_HEIGHT);
	ZeroMemory(m_iWalkableMap, sizeof(int)*MAP_WIDTH*MAP_HEIGHT);
	m_pLeftMap = 0;
	m_pRightMap = 0;
	m_pUpMap = 0;
	m_pDownMap = 0;
}

bool CMap::ReadMapFile(std::string strFileName, CMap* pMap)
{
	std::ifstream filestream;
	filestream.open(strFileName.c_str());
	if (!filestream.is_open()) { return false; }
	//Read map id
	filestream>>m_iMapID;
	//Read sprite map
	//{
	for (int iHeightIndex=0; iHeightIndex<MAP_HEIGHT; iHeightIndex++)
	{
		for (int iWidthIndex=0; iWidthIndex<MAP_WIDTH; iWidthIndex++)
		{
			filestream>>m_iMap[iHeightIndex][iWidthIndex];
		}
	}
	//}
	int iTemp;
	//Read connecting map id
	//{
	filestream>>iTemp;
	if (iTemp != -1)
		m_pLeftMap = (pMap+iTemp);
	filestream>>iTemp;
	if (iTemp != -1)
		m_pRightMap = (pMap+iTemp);
	filestream>>iTemp;
	if (iTemp != -1)
		m_pUpMap = (pMap+iTemp);
	filestream>>iTemp;
	if (iTemp != -1)
		m_pDownMap = (pMap+iTemp);
	//}

	//Read walkable map
	//{
	for (iHeightIndex=0; iHeightIndex<MAP_HEIGHT; iHeightIndex++)
	{
		for (int iWidthIndex=0; iWidthIndex<MAP_WIDTH; iWidthIndex++)
		{
			filestream>>m_iWalkableMap[iHeightIndex][iWidthIndex];
		}
	}
	//}
	std::string strTemp;

	std::getline(filestream, strTemp);

	std::getline(filestream, m_strMapName);

	filestream.close();
	return true;
}
