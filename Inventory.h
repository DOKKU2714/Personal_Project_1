#pragma once
#include "item.h"

class C_INVENTORY
{
private:
	C_ITEM** *	m_pppItemSpace;	//�������� �ϸ� �� ��Ҵ� ��ü ��ü�� ���� ������ ������ ����
	int			m_nXSize;
	int			m_nYSize;

private:
	bool canPlaceItem(C_ITEM* pItem, int nX, int nY);			//�ش� space�������� ������ ũ�⸸ŭ ������ �ִ��� üũ
	void placeItem(C_ITEM* pItem, int nX, int nY);
	int addItem(C_ITEM* pItem, int nCount, int nX, int nY);
	C_ITEM* getItem(int nX, int nY);
	C_ITEM* copyItem(C_ITEM* pItem);
	int clean();

public:
	void init(int nXSize, int nYSize);

	bool autoInsertItem(C_ITEM* pItem, int nCount);				//�ڵ����� �κ��丮�� ����
	bool moveItem(int nItemX, int nItemY, int nMoveX, int nMoveY);					//�������� Ư�� ��ġ�� �̵�
	bool dropItem(C_ITEM* pItem, int nCount);					//Ư�� ������ ����


	void print();

	bool release();
};
