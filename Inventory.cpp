#include "Inventory.h"


bool C_INVENTORY::canPlaceItem(C_ITEM* pItem, int nX, int nY)
{
	int nItemSizeX = pItem->getXSize();
	int nItemSizeY = pItem->getYSize();

	if (m_nXSize < nX + nItemSizeX || m_nYSize < nY + nItemSizeY)
		return false;

	for (int y = nY; y < nItemSizeY + nY; y++)
	{
		for (int x = nX; x < nItemSizeX + nX; x++)
		{
			if (m_pppItemSpace[x][y] != nullptr)
				return false;
		}
	}

	return true;
}

void C_INVENTORY::init(int nXSize, int nYSize)
{	
	m_nXSize = nXSize;
	m_nYSize = nYSize;

	m_pppItemSpace = new C_ITEM ** [m_nXSize] {};
	for (int i = 0; i < m_nXSize; i++)
	{
		m_pppItemSpace[i] = new C_ITEM *[m_nYSize]{};

		for (int j = 0; j < m_nYSize; j++)
		{
			m_pppItemSpace[i][j] = nullptr;
		}
	}
}

void C_INVENTORY::placeItem(C_ITEM* pItem,  int nX, int nY)
{
	C_ITEM* pCopyItem = copyItem(pItem);	//place 할 때만 객체가 다른 주소값을 갖도록함 (개수 수정 시 안 겹치는 것들도 겹쳐져서)
	for (int i = nX; i < (pItem->getXSize()) + nX; i++)
	{
		for (int j = nY; j < (pItem->getYSize()) + nY; j++)
		{
			m_pppItemSpace[i][j] = pCopyItem;
			m_pppItemSpace[i][j]->setCount(1);
		}
	}
}

C_ITEM* C_INVENTORY::copyItem(C_ITEM* pItem)
{
	C_ITEM* pCopyItem = new C_ITEM{};
	pCopyItem->init(pItem->getItemId(), pItem->getXSize(), pItem->getYSize(), pItem->getOverlapableCount());

	return pCopyItem;
}

int C_INVENTORY::clean()
{
	int nCleanCount{};

	for (int i = 0; i < m_nXSize; i++)
	{
		for (int j = 0; j < m_nYSize; j++)
		{
			if (m_pppItemSpace[i][j] != nullptr 
				&& m_pppItemSpace[i][j]->getCount() <= 0)
			{
				m_pppItemSpace[i][j] = nullptr;
				delete m_pppItemSpace[i][j];
				nCleanCount++;
			}
		}
	}
	return nCleanCount;
}


//3중 포인터를 해야 역참조를 2번 했을 때 객체의 주소값이 나온다.
//place 할 땐 새로운 객체를 복사해서 place 해야함...
bool C_INVENTORY::autoInsertItem(C_ITEM* pItem, int nCount)
{
	int nItemSizeX = pItem->getXSize();
	int nItemSizeY = pItem->getYSize();
	int nX{};
	int nY{};
	C_ITEM* pInvItem{};

	while (nCount > 0)
	{
		pInvItem = m_pppItemSpace[nX][nY];

		while (pInvItem != nullptr
				&& pInvItem->getItemId() == pItem->getItemId()
				&& pInvItem->getOverlapableCount() > pInvItem->getCount()
				&& nCount > 0)
		{
			pInvItem->addCount(1);
			nCount--;
		}

		if (pInvItem == nullptr 
				&& canPlaceItem(pItem, nX, nY))
		{
			placeItem(pItem, nX, nY);
			nCount--;
		}

		nX++;
		if (nX >= m_nXSize)
		{
			nX = 0;
			nY++;
		}
	}

	return true;
}
/*
* 현재 상황
*	인벤토리의 빈 공간을 nullptr로 설정하려니 while문의 로직이 꼬이고
*		nullptr 접근 시 에러가 너무 많이 발생
*			따라서,
*				빈 공간은 무조건 아이디를 0으로 바꾸는 작업 필요
*					위 모든 로직 다 수정 필요하며 clean 함수 재작업 필요
*/
bool C_INVENTORY::moveItem(int nItemX, int nItemY, int nTargetX, int nTargetY)
{
	/*
	* 타겟에 이미 아이템이 존재하는경우
	*	옮길 아이템의 수 만큼 타겟 아이템의 개수를 최대치까지 채운다.
	*		그러고 옮길 아이템의 수가 남는경우 
				기존 아이템은 해당 수 로 남긴다.
	*		옮긴 아이템의 수가 안남는경우
	*			기존 아이템 삭제
	* 
	* 타겟에 아이템이 없는 경우
	*	타겟 위치에 아이템 크기만큼 여유공간 존재하는지 확인
	* 
	* 
	*/
	C_ITEM* pItem = m_pppItemSpace[nItemX][nItemY];

	while (pItem->getCount() > 0)
	{
		C_ITEM* pTargetItem = m_pppItemSpace[nTargetX][nTargetY];


		while (pTargetItem != nullptr
			&& pTargetItem->getItemId() == pItem->getItemId()
			&& pTargetItem->getOverlapableCount() > pTargetItem->getCount())
		{
			pTargetItem->addCount(1);
			pItem->addCount(-1);
		}

		if (pTargetItem == nullptr
			&& canPlaceItem(pItem, nTargetX, nTargetY))
		{
			placeItem(pItem, nTargetX, nTargetY);
			pItem->addCount(-1);
		}

		if (pTargetItem != nullptr
			&& pTargetItem->getOverlapableCount() == pTargetItem->getCount())
		{
			return true;
		}
	}
			printf("%d개 삭제됨 \n",clean());

	return true;
}

void C_INVENTORY::print()
{
	for (int i = 0; i < m_nYSize; i++)
	{
		for (int j = 0; j < m_nXSize; j++)
		{
			if (m_pppItemSpace[j][i] == nullptr)
				printf("0 ");
			else 
				printf("%d ", m_pppItemSpace[j][i]->getItemId());
		}
		printf("\n");
	}
	printf("\n");
	printf("개수\n");
	for (int i = 0; i < m_nYSize; i++)
	{
		for (int j = 0; j < m_nXSize; j++)
		{
			if (m_pppItemSpace[j][i] == nullptr)
				printf("0 ");
			else
				printf("%d ", m_pppItemSpace[j][i]->getCount());
		}
		printf("\n");
	}
}

bool C_INVENTORY::release()
{
	delete[] m_pppItemSpace;
	m_pppItemSpace = nullptr;
	return true;
}
