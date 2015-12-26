#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iosfwd>

template <class Type>
class LinkedList {
public:
	LinkedList( );

	LinkedList(const LinkedList& rhs);

	~LinkedList( );

	void appendToHead(Type data);

	void append(Type data);

	void appendAtIndex(Type data, int index);

	Type dataAtHead( ) const;

	Type dataAtTail( ) const;

	Type dataAtIndex(int index) const;
	
	Type find (Type data) const;

	void insert(Type data);

	int getSize( ) const;

	bool remove(Type data);

	LinkedList& operator=(const LinkedList& rhs);

	friend std::ostream& operator<<(std::ostream& output, const LinkedList<Type>& currentList) {
		if (currentList.size == 0) {
			output << "The list is empty.\n";
		}
		Node* current = currentList.head;
		while (current != nullptr) {
			output << *current->data << "\n";
			current = current->next;
		}
		return output;
	}
protected:
	struct Node {
		Type data;
		Node* next;

		Node (Type data);
		Node (Type data, Node* next);
	};
	Node* head;
	Node* tail;
	int size;
};

template <class Type>
LinkedList<Type>::Node::Node(Type data) : data(data), next(nullptr) { }

template <class Type>
LinkedList<Type>::Node::Node(Type data, Node* next) : data(data), next(next) { }

template <class Type>
LinkedList<Type>::LinkedList( ) : head(nullptr), tail(nullptr), size(0) { }

template <class Type>
LinkedList<Type>::LinkedList(const LinkedList& rhs) : head(nullptr), tail(nullptr), size(0) {
	if (rhs.head != nullptr) {
		head = new Node (rhs.head->data);
		++size;
		Node* current = head;
		Node* rhsCurrent = rhs.head->next;
		while (rhsCurrent != nullptr) {
			current->next = new Node (rhsCurrent->data);
			++size;
			current = current->next;
			rhsCurrent = rhsCurrent->next;
		}
		tail = current;
	}
}

template <class Type>
LinkedList<Type>::~LinkedList( ) {
	while (head != nullptr) {
		Node* tempNext = head->next;
		delete head;
		head = tempNext;
	}
	head = nullptr;
	tail = nullptr;
}

template <class Type>
void LinkedList<Type>::appendToHead(Type data) {
	head = new Node(data, head);
	if (size == 0) {
		tail = head;
	}
	size++;
}

template <class Type>
void LinkedList<Type>::append(Type data) {
	if (size != 0) {
		tail->next = new Node(data);
		tail = tail->next;
		++size;
	} else {
		appendToHead (data);
	}
}

template <class Type>
void LinkedList<Type>::appendAtIndex(Type data, int index) {
	if (index < 0 || index >= size) {
		return;
	}
	if (index == 0) {
		appendAtHead (data);
		return;
	}
	if (index == size - 1) {
		append (data);
		return;
	}
	Node* current = head;
	for (int i = 0; i < index; ++i) {
		current = current->next;
	}
	current->next = new Node(data, current->next);
	++size;
}

template <class Type>
Type LinkedList<Type>::dataAtHead( ) const {
	if(head != nullptr) {
		return head->data;
	}
	return nullptr;
}

template <class Type>
Type LinkedList<Type>::dataAtTail( ) const {
	if (tail != nullptr) {
		return tail->data;
	}
	return nullptr;
}

template <class Type>
Type LinkedList<Type>::dataAtIndex(int index) const {
	if (index >= 0 || index < size) {
		if (index == 0) { return dataAtHead(); }
		if (index == size - 1) { return dataAtTail(); }

		Node* current = head;
		for (int i = 0; i < index; ++i) {
			current = current->next;
		}
		return current->data;
	}
	return nullptr;
}

template <class Type>
Type LinkedList<Type>::find(Type data) const {
	if (head == nullptr) { return nullptr; }
	Node* current = head;
	while(current != nullptr) {
		if(*current->data == *data) {
			return current->data;
		}
		current = current->next;
	}
	return nullptr;
}

template <class Type>
void LinkedList<Type>::insert(Type data) {
	if (head == nullptr) {
		head = new Node(data);
		tail = head;
	} else if (*data <= *head->data) {
		head = new Node(data, head);
	} else {
		Node* previous = head;
		Node* current = head->next;
		while (current != nullptr && *data > *current->data) {
			previous = current;
			current = current->next;
		}
		previous->next = new Node(data, current);
		if (previous == tail) {
			tail = previous->next;
		}
	}
	++size;
}

template <class Type>
int LinkedList<Type>::getSize( ) const {
	return size;
}

template <class Type>
bool LinkedList<Type>::remove(Type data) {
	if (head == nullptr) {
		return false;
	}
	Node* previous = nullptr;
	Node* current = head;
	while (current != nullptr && data != current->data) {
		previous = current;
		current = current->next;
	}
	if (current == nullptr) { return false; }	// If current is null, the parameter pass was not found.
	if (current == head) { head = head->next; } // Update the head if node found is at the head.
	if (current == tail) { tail = previous; }	// Update the tail if the node found is at the tail.
	if (previous != nullptr) {
		previous->next = current->next;			// Update the previous nodes next.
	}
	delete current;								// Delete the node found.
	--size;
	return true;
}

template <class Type>
LinkedList<Type>& LinkedList<Type>::operator=(const LinkedList& rhs) {
	if (this != &rhs) {
		while (head != nullptr) {
			Node* temp = head->next;
			delete head;
			head = temp;
		}

		head = nullptr;
		tail = nullptr;
		size = 0;
		if (rhs.head != nullptr) {
			head = new Node (rhs.head->data);
			++size;
			Node* current = head;
			Node* rhsCurrent = rhs.head->next;
			while (rhsCurrent != nullptr) {
				current->next = new Node (rhsCurrent->data);
				++size;
				current = current->next;
				rhsCurrent = rhsCurrent->next;
			}
			tail = current;
		}
	}
	return *this;
}
#endif //LINKEDLIST_HPP