// Hand.cpp
// Created by Evan Almonte
//
#include "Hand.hpp"

Hand::Hand ( ) : LinkedList<Card*> ( ) {}

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
			groupCount == 1;
		}
		current = current->next;
	}
	return nullptr;
}