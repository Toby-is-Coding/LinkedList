#include "LinkedList.h"
#include <iostream>
LL::LL()
	: head(NULL), _size(0)
{
}

LL::LL(int size)
	: head(NULL), _size(size)
{
	if (size > 0) {
		//create head node
		Node* tmp = new Node;
		head = tmp;
		head->ptr = NULL;
		head->data = NULL;
		if (size > 1) {
			//create second node (head node must point to it)
			Node* it;
			tmp = new Node;
			it = tmp;
			head->ptr = it; //(head node does point to it)
			it->data = NULL;
			it->ptr = NULL;
			for (int i = 2; i < size; i++) { //rest of nodes
				tmp = new Node; //create next node
				it->ptr = tmp; //set current node's ptr to point to next node
				it = tmp; //iterate over to next node
				it->data = NULL; //set data to null
			}
			it->ptr = NULL; //set ptr to null
		}
	}
}

LL::LL(const LL& LL)
	:head(NULL), _size(LL._size)
{
	if (_size > 0) {
		//create head node
		Node* tmp = new Node;
		head = tmp;
		head->ptr = NULL;
		head->data = LL.head->data;
		if (_size > 1) {
			//create second node (head node must point to it)
			Node* itself, * itnelf = LL.head->ptr; //iterator of the self, iterator of the nelf.
			tmp = new Node;
			itself = tmp;
			head->ptr = itself; //(head node does point to it)
			itself->data = itnelf->data; //copy data from other Linked List
			itself->ptr = NULL;
			for (int i = 2; i < _size; i++) { //rest of nodes
				tmp = new Node; //create next node
				itself->ptr = tmp; //set current node's ptr to point to next node
				itself = tmp; //iterate over to next node
				itself->data = itnelf->data; //copy data from other Linked List
			}
			itself->ptr = NULL; //set ptr to null
		}
	}
}

LL::~LL()
{
	Node* tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->ptr;
		delete tmp;
	}
	if (arr != nullptr) delete[] arr;
}

const int LL::size() const
{
	return _size;
}

void LL::erase(unsigned index, unsigned plus)
{
	if (index < 0 || index >= _size) {
		return; //out of scope
	}
	if (plus > _size - 1) plus = _size - index - 1; //if plus too big, erase until the end
	_size -= plus + 1; //update size
	Node* tmp;
	if (index == 0) { //delete first object (head's node)
		for (int i = 0; i <= plus; i++) {
			tmp = head; //save head for later deletion
			head = head->ptr; //iterate head over
			delete tmp; //arrival of later deletion
		}
		return;
	}
	Node* it = head;
	for (int i = 1; i < index - 1 + plus; i++) { //loop up to 1 before index, + number of things we want to delete after
		it = it->ptr; //iterate until 1 node before the node we want to delete
		if (i >= index - 1) { //reached point where we want to start deleting ptrs
			tmp = it->ptr; //                                    [2] -v
			it->ptr = it->ptr->ptr; // [1] -> [2] -> [3] // [1] -> -> [3] // delete [2]
			delete tmp;
		}
	}
}

void LL::insert(Node** nodes, unsigned index, unsigned amount)
{
	_size += amount; //update size
	if (*nodes == NULL) return; //bye bye to nullify

	if (head == NULL) { //if size == 0 basically but more exact
		Node* tmp = *nodes;
		head = tmp;
		head->ptr = NULL;
		if (amount > 1) { //for second node
			tmp = nodes[1];
			head->ptr = tmp;
			Node* it = tmp;
			for (int i = 2; i < amount; i++) { //rest of nodes
				tmp = nodes[i];
				it->ptr = tmp;
				it = tmp;
			}
		}
		return;
	}

	if (index <= 0) { //insert node at start of LL (new head)
		Node* tmp = head; //save head as tmp
		head = *nodes; //set head to first obj in nodes
		if (amount == 1) head->ptr = tmp; //if only 1 node inserted, connect new head with old head
		else {
			head->ptr = nodes[1]; //else, connect with second obj
			Node* it = nodes[1];
			for (int i = 2; i < amount; i++) {
				it->ptr = nodes[i]; //point to next obj
				it = nodes[i]; //become next obj
			}
			it->ptr = tmp; //reconnect with old head (and thus all of the old nodes)
		}
		return;
	}

	if (index > _size) index = _size; //set to insert node at end of LL

	for (int i = 0; i < amount; i++) {
		(*(*this)[index - 1 + i]).cut(nodes[i]); //cut in front of the node before the node at index
	}
	return;
}

void LL::flood(int data, unsigned start, int end)
{
	if (end < 0 || end >= _size) {
		end = _size - 1; //default argument
	}
	if (head != NULL) {
		Node* it = head;
		for (int i = 0; i <= end; i++) {
			if (i >= start) it->data = data; //only assign data after iterator's reached the starting position
			it = it->ptr; //iterate over to next node
		}
	}
}

void LL::print()
{
	if (head == NULL) return; //LL of nothing
	Node* it = head;
	for (int i = 0; i < _size - 1; i++) {
		std::cout << '[' << it->data << "], ";
		it = it->ptr;
	}
	std::cout << '[' << it->data << ']' << std::endl;
}

const size_t LL::size_of()
{
	Node* it = head;
	size_t S = it != NULL ? 0 : sizeof it;
	while (it != NULL) {
		S += sizeof(it);
		it = it->ptr;
	}
	return S;
}

Node* LL::operator()(unsigned index)
{
	if (index < 0 || index >= _size) {
		return nullptr;
	}
	Node* it = head;
	for (int i = 0; i < index; i++) {
		it = it->ptr;
	}
	return it;
}

LL::operator Node** ()
{
	if (_size == 0) return nullptr;
	arr = new Node*[_size];
	Node* it = head, * tmp;
	for (int i = 0; i < _size; i++) {
		tmp = new Node; //create new so we point to copies of the nodes instead of the nodes themselves
		tmp->data = it->data; //copy copy
		tmp->ptr = NULL;
		arr[i] = tmp; //save to array!
		it = it->ptr; //iterate forth!
	}
	return arr; //implicit casting of Node* array to Node**
}

/*std::ostream& operator<<(std::ostream os, const LL& ll)
{
	Node* it = ll.head;
	for (int i = 0; i < ll._size - 1; i++) {
		os << '[' << it->data << "], ";
		it = it->ptr;
	}
	os << '[' << it->data << ']';
	return os;
}*/
