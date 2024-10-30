#include <iostream>
#include "Item.h"
#include "Inventory.h"

int main()
{
	C_ITEM cItem{};
	cItem.init(1, 2, 2, 2);

	C_ITEM cItem2{};
	cItem2.init(2, 3, 1, 3);	

	//C_ITEM cItem9{};
	//cItem9.init(9, 1, 8, 5);	


	C_INVENTORY cInventory{};
	cInventory.init(10, 11);

	cInventory.autoInsertItem(&cItem, 1);
	cInventory.autoInsertItem(&cItem, 1);
	cInventory.autoInsertItem(&cItem, 1);
	cInventory.moveItem(1, 0, 3, 0);
	cInventory.moveItem(3, 0, 0, 0);
	cInventory.moveItem(0, 0, 5, 0);
	//cInventory.autoInsertItem(&cItem2, 1);
	//cInventory.autoInsertItem(&cItem2, 1);

	//cInventory.autoInsertItem(&cItem9, 1);
	//cInventory.autoInsertItem(&cItem9, 6);
	//cInventory.autoInsertItem(&cItem9, 6);
	//cInventory.autoInsertItem(&cItem9, 6);


	cInventory.print();

	cInventory.release();
}
