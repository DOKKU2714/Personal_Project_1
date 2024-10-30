#pragma once
#include <string>
#include <stdio.h>
class C_ITEM
{
private:
	std::string			m_strUniqueId;		//아이템 생성 시 마다 다름
	int					m_nId;				//어떤 아이템인지
	std::string			m_strName;
	std::string			m_strDescript;
	int					m_nRarity;

	int					m_nCount;
	int					m_nOverlapableCount;
	int					m_nXSize;
	int					m_nYSize;

public:
	C_ITEM() = default;

	void init(int nId);							//UniqueId 생성, 외부 리소스를 통해 맴버 세팅 (uniqueId빼고)
	void init(int nId, int nXSize, int nYSize);			
	void init(int nId, int nXSize, int nYSize, int nOverlapableCount);

	int getItemId();
	int getXSize();
	int getYSize();
	int getCount();
	void setCount(int nCount);
	void addCount(int nCount);
	int getOverlapableCount();
	bool isEmpty();
	void print();

};