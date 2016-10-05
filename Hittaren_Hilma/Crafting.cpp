#include "Crafting.h"

Crafting::Crafting()
{

}

Crafting::~Crafting()
{

}

//Crafting function, where you combine items to create a result (a new item)
void Crafting::combineItems(Item *item, Item *item2, Item *result)
{
	//Recipe setup, depends on index
	if (item->getIndex() == 0 && item2->getIndex() == 1 || item->getIndex() == 1 && item2->getIndex() == 0)
	{
		//mInventory->removeItem(item);
		//mInventory->removeItem(item2);
		mInventory->addItem(result);
	}
}