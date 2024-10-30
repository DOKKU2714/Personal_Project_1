#pragma once
#include "item.h"

class C_INVENTORY
{
private:
	C_ITEM** *	m_pppItemSpace;	//이중으로 하면 각 요소는 객체 자체를 갖기 때문에 문제가 생김
	int			m_nXSize;
	int			m_nYSize;

private:
	bool canPlaceItem(C_ITEM* pItem, int nX, int nY);			//해당 space기준으로 아이템 크기만큼 공간이 있는지 체크
	void placeItem(C_ITEM* pItem, int nX, int nY);
	int addItem(C_ITEM* pItem, int nCount, int nX, int nY);
	C_ITEM* getItem(int nX, int nY);
	C_ITEM* copyItem(C_ITEM* pItem);
	int clean();

public:
	void init(int nXSize, int nYSize);

	bool autoInsertItem(C_ITEM* pItem, int nCount);				//자동으로 인벤토리에 삽입
	bool moveItem(int nItemX, int nItemY, int nMoveX, int nMoveY);					//아이템을 특정 위치로 이동
	bool dropItem(C_ITEM* pItem, int nCount);					//특정 아이템 삭제


	void print();

	bool release();
};
