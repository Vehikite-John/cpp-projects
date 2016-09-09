// LinkedListPractice.cpp
// Test Linked List class
//

#include "stdafx.h"
#include "List.h"
#include <iostream>

int main()
{
	// Create list
	List list;
	
	// add values to list
	list.addNode(1);
	list.deleteNode();
	list.addNode(2);
	
	// display list
	list.displayList();
    return 0;
}

