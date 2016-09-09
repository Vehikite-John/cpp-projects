#include "List.h"
#include <cstdlib> // for NULL
#include <iostream> // for cout

// Default constructor
// Create an empty list
List::List()
{
	head = NULL;
}

List::~List()
{
	// TODO: Create code to delete entire list
}

// add node to list
// CURRENT VERSION: adds node to beginning of list with data = argument
// FUTURE RELEASE: add to end or middle; needs int pos parameter
void List::addNode(int data)
{
	Node * temp = new Node;
	temp->data = data;
	
	// if list is empty
	if (head == NULL)
	{
		temp->next = NULL;
	}

	// if list is not empty, make next point to head
	else
	{
		temp->next = head;
	}

	// move head to front of list
	head = temp;
	std::cout << "Node " << data << " was added to the front of the list\n";
}

// deletes node from list
// CURRENT VERSION: deletes node to beginning of list
// FUTURE RELEASE: delete node at end or middle; needs int pos parameter
void List::deleteNode()
{
	// list is already empty
	if (!head)
	{
		std::cout << "List is already empty.\n";
	}

	std::cout << "Node " << head->data << " has been deleted.\n";

	// only one element in linked list
	if (!head->next)
	{
		head = NULL;
	}

	else
	{
		Node * temp = head;
		head = head->next;
		delete temp;
	}
}

// display list
void List::displayList()
{
	if (!head)
	{
		std::cout << "List is empty.\n";
	}

	else
	{
		std::cout << "Here are the contents of the list:\n";
		// while head != NULL
		while (head)
		{
			std::cout << "Node " << head->data << std::endl;
			head = head->next;
		}
	}
}
