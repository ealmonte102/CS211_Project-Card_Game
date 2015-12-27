// Linkedlist.cpp
// Created by Evan Almonte
//  
#include "Linkedlist.hpp"

template <>
inline void LinkedList<Card*>::insert (Card* data) {
	if (head == nullptr) {
		head = new Node (data);
		tail = head;
	} else if (data->compareByRank (*head->data) <= 0) {
		head = new Node (data, head);
	} else {
		Node* previous = head;
		Node* current = head->next;
		while (current != nullptr && data->compareByRank (*current->data) > 0) {
			previous = current;
			current = current->next;
		}
		previous->next = new Node (data, current);
		if (previous == tail) {
			tail = previous->next;
		}
	}
	++size;
}

template LinkedList<Card*>;