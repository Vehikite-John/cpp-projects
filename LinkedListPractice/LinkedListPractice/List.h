#pragma once

// FUTURE RELEASE: create template
struct Node
{
	int data;
	Node * next;
};

class List
{
public:
	// default constructor
	List();
	
	// destructor
	~List();

	void addNode(int data);
	void deleteNode();
	void displayList();

private:
	Node * head;
	// Node * curr;
	// Node * temp;
};

