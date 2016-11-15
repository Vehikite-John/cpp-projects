// DoublyLinkedListExample.cpp : Defines the entry point for the console application.
//

// source: https://www.youtube.com/playlist?list=PLTxllHdfUq4dp5Hrsw3FJzI1nnlXBre0v

#include "stdafx.h"
#include <cstdlib>
#include <iostream>

// node struct
// outside of main so functions can use the struct
struct node
{
	int data;

	// two nodes to point both ways in list
	node * next;
	node * prev;
};

void printFoward(node * head);
void printBackward(node * tail);

int main()
{
	node * head;
	node * tail;
	node * n;		// new node
	
	// create 1st node
	n = new node;
	n->data = 1;
	n->prev = NULL;
	// only one node, so make head and tail equal to new node n
	head = n;
	tail = n;

	// create 2nd node
	n = new node;
	n->data = 2;
	n->prev = tail;		
	tail->next = n;
	// move tail to the tail end of the list
	tail = n;			

	n = new node;
	n->data = 3;
	n->prev = tail;
	tail->next = n;
	tail = n;

	n = new node;
	n->data = 4;
	n->prev = tail;
	tail->next = n;
	tail = n;
	tail->next = NULL;

	printFoward(head);
	printBackward(tail);

    return 0;
}

void printFoward(node * head)
{
	node * temp = head;

	while (temp != NULL)
	{
		std::cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}

void printBackward(node * tail)
{
	node * temp = tail;

	while (temp != NULL)
	{
		std::cout << temp->data << " ";
		temp = temp->prev;
	}
	std::cout << std::endl;
}