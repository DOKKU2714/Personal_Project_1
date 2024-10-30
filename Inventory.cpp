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
	C_ITEM* pCopyItem = copyItem(pItem);	//place �� ���� ��ü�� �ٸ� �ּҰ��� �������� (���� ���� �� �� ��ġ�� �͵鵵 ��������)
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


//3�� �����͸� �ؾ� �������� 2�� ���� �� ��ü�� �ּҰ��� ���´�.
//place �� �� ���ο� ��ü�� �����ؼ� place �ؾ���...
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
* ���� ��Ȳ
*	�κ��丮�� �� ������ nullptr�� �����Ϸ��� while���� ������ ���̰�
*		nullptr ���� �� ������ �ʹ� ���� �߻�
*			����,
*				�� ������ ������ ���̵� 0���� �ٲٴ� �۾� �ʿ�
*					�� ��� ���� �� ���� �ʿ��ϸ� clean �Լ� ���۾� �ʿ�
*/
bool C_INVENTORY::moveItem(int nItemX, int nItemY, int nTargetX, int nTargetY)
{
	/*
	* Ÿ�ٿ� �̹� �������� �����ϴ°��
	*	�ű� �������� �� ��ŭ Ÿ�� �������� ������ �ִ�ġ���� ä���.
	*		�׷��� �ű� �������� ���� ���°�� 
				���� �������� �ش� �� �� �����.
	*		�ű� �������� ���� �ȳ��°��
	*			���� ������ ����
	* 
	* Ÿ�ٿ� �������� ���� ���
	*	Ÿ�� ��ġ�� ������ ũ�⸸ŭ �������� �����ϴ��� Ȯ��
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
			printf("%d�� ������ \n",clean());

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
	printf("����\n");
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
