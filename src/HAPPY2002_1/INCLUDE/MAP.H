// Map.h: interface for the CMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_H__7BEF2A5B_CA45_4061_95E7_B7DBDE2D915E__INCLUDED_)
#define AFX_MAP_H__7BEF2A5B_CA45_4061_95E7_B7DBDE2D915E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <fstream>

#define MAP_WIDTH 15
#define MAP_HEIGHT 11

class CMap  
{
	CMap *m_pLeftMap, *m_pRightMap, *m_pUpMap, *m_pDownMap;
	std::string m_strMapName;
	unsigned int m_iMapID;
public:
	bool ReadMapFile(std::string strFileName, CMap* pMap);
	void CleanUp();
	CMap();
	virtual ~CMap();
	int m_iMap[MAP_HEIGHT][MAP_WIDTH];
	int m_iWalkableMap[MAP_HEIGHT][MAP_WIDTH];
	CMap* getLeftMap() { return m_pLeftMap; }
	CMap* getRightMap() { return m_pRightMap; }
	CMap* getUpMap() { return m_pUpMap; }
	CMap* getDownMap() { return m_pDownMap; }
	std::string getMapName() { return m_strMapName; }
	unsigned int getMapID() { return m_iMapID; }
};

#endif // !defined(AFX_MAP_H__7BEF2A5B_CA45_4061_95E7_B7DBDE2D915E__INCLUDED_)
