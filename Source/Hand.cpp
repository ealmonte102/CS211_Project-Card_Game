﻿// Hand.cpp
// Created by Evan Almonte
//
#include "Hand.hpp"
#include "Card.hpp"
#include <iostream>

using std::cout;

Hand::Hand ( ) : LinkedList<Card*> ( ) {}

int Hand::evaluate( ) {
	Node* foundGroup = findGroup ( );
	if(foundGroup != nullptr) {
		removeGroup (foundGroup);
		return 1 + evaluate ( );
	}
	return 0;
}

bool Hand::findRank(Card& card) const {
	Node* current = head;
	while(current != nullptr) {
		if(current->data->compareByRank(card) == 0) {
			return true;
		}
		current = current->next;
	}
	return false;
}

void Hand::removeGroup (Node* node) {
	if (node == nullptr) { return; }
	Node* previous = nullptr;
	Node* current = head;
	while (current != node) {
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
	if (previous == nullptr) {
		head = afterDelete;
	} else if (previous == head) {
		head->next = afterDelete;
	} else {
		previous->next = afterDelete;
	}
	if(afterDelete == nullptr) {
		tail = previous;
	}
}

LinkedList<Card*>::Node* Hand::findGroup( ) const {
	if (head == nullptr) { return nullptr; }
	Node* current = head;
	Node* startOfGroup = head;
	int groupCount = 1;
	while(current->next != nullptr) 
	{
		if (startOfGroup->data->compareByRank(*current->next->data) == 0) {
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

std::ostream& operator<<(std::ostream& output, const Hand& aHand) {
	Hand::Node* current = aHand.head;
	int numPrinted = 0;
	while(current != nullptr) {
		cout << *current->data;
		if(current->next != nullptr) {
			cout << " | ";
			if ((numPrinted + 1) % 10 == 0) {
				cout << "\n";
			}
			numPrinted++;
		}
		current = current->next;
	}
	return output;
}
