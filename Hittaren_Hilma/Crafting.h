#ifndef CRAFTING
#define CRAFTING

#include "Inventory.h"

class Crafting
{
public:
	Crafting();
	~Crafting();

	//Function to combine items
	void combineItems(Item *item, Item *item2, Item *result);
private:
	Inventory *mInventory;
};

#endif