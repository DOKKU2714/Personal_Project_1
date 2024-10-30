#pragma once
#include <string>
#include <stdio.h>
class C_ITEM
{
private:
	std::string			m_strUniqueId;		//������ ���� �� ���� �ٸ�
	int					m_nId;				//� ����������
	std::string			m_strName;
	std::string			m_strDescript;
	int					m_nRarity;

	int					m_nCount;
	int					m_nOverlapableCount;
	int					m_nXSize;
	int					m_nYSize;

public:
	C_ITEM() = default;

	void init(int nId);							//UniqueId ����, �ܺ� ���ҽ��� ���� �ɹ� ���� (uniqueId����)
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