// Hand.cpp
// Created by Evan Almonte
//
#include "Hand.hpp"

Hand::Hand ( ) : LinkedList<Card*> ( ) {}

void Hand::removeGroup(Node* node) {
	if (node == nullptr) { return; }
	Node* previous = head;
	Node* current = head;
	while(current != node) {
		previous = current;
		current = current->next;
	}
	Node* afterDelete = nullptr;
	for (int i = 0; i < 4; i++) {
		afterDelete = current->next;
		delete current;
		--size;
		current = afterDelete;
	}
	if(previous != head) {
		previous->next = afterDelete;
	} else {
		head = afterDelete;
	}
}

LinkedList<Card*>::Node* Hand::findGroup( ) const {
	if (head == nullptr) { return nullptr; }
	Node* current = head;
	Node* startOfGroup = head;
	int groupCount = 1;
	while(current->next != nullptr) 
	{
		if (startOfGroup->data == current->next->data) {
			groupCount++;
			if (groupCount == 4) { return startOfGroup; }
		} else {
			startOfGroup = current->next;
			groupCount = 1;
		}
		current = current->next;
	}
	return nullptr;
}