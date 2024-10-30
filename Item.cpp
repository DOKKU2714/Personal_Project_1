#include "Item.h"

void C_ITEM::init(int nId)
{
	m_strUniqueId = "test1234";
	m_strName = "testItem";
	m_strDescript = "testDescription";
	m_nId = nId;
	m_nOverlapableCount = 1;
	m_nRarity = 0;
	m_nXSize = 2;
	m_nYSize = 2;
}

void C_ITEM::init(int nId, int nXSize, int nYSize)
{
	init(nId);
	m_nXSize = nXSize;
	m_nYSize = nYSize;
}

void C_ITEM::init(int nId, int nXSize, int nYSize, int nOverlapableCount)
{
	init(nId, nXSize, nYSize);
	m_nOverlapableCount = nOverlapableCount;
}

int C_ITEM::getItemId()
{
	return m_nId;
}

int C_ITEM::getXSize()
{
	return m_nXSize;
}

int C_ITEM::getYSize()
{
	return m_nYSize;
}

int C_ITEM::getCount()
{
	return m_nCount;
}

void C_ITEM::setCount(int nCount)
{
	m_nCount = nCount;
}

void C_ITEM::addCount(int nCount)
{
	m_nCount += nCount;
}

int C_ITEM::getOverlapableCount()
{
	return m_nOverlapableCount;
}

bool C_ITEM::isEmpty()
{
	if (m_nId == 0)
		return true;
	return false;
}

void C_ITEM::print()
{
	printf("%s : %d\n", m_strName, m_nId);
}

