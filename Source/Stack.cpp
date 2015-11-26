#include "Stack.hpp"
#include "Card.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

Stack::Stack ( ) : capacity (52), size (0), stack (new Card*[capacity]) { }

Stack::Stack (int c) : size (0) {
	if (c < 0) {
		capacity = 52;
	}
	capacity = c;
	stack = new Card*[capacity];
}

Stack::Stack (const Stack& rhs) : capacity (rhs.capacity), size (rhs.size), stack (new Card*[capacity]) {
	for (int i = 0; i < size; ++i) {
		stack[i] = new Card (*rhs.stack[i]);
	}
}

Stack::~Stack ( ) {
	for (int i = 0; i < size; ++i) {
		delete stack[i];
	}
	delete[] stack;
	stack = nullptr;
}

int Stack::getSize ( ) const {
	return size;
}

int Stack::getTotalCapacity ( ) const {
	return capacity;
}

bool Stack::isEmpty ( ) const {
	return size == 0;
}

bool Stack::isFull ( ) const {
	return size == capacity;
}

Card* Stack::peek ( ) const {
	if (!isEmpty ( )) {
		return stack[size - 1];
	}
	return nullptr;
}

Card* Stack::pop ( ) {
	if (!isEmpty ( )) {
		Card* topCard = stack[size - 1];
		stack[--size] = nullptr;
		return topCard;
	}
	return nullptr;
}

void Stack::push (Card* c) {
	if (!isFull ( )) {
		stack[size++] = c;
	} else {
		cout << "Stack is full!" << endl;
	}
}

Stack& Stack::operator=(const Stack& rhs) {
	if (this != &rhs) {
		for (int i = 0; i < size; ++i) {
			delete stack[i];
		}
		delete[] stack;
		stack = nullptr;

		capacity = rhs.capacity;
		size = rhs.size;
		stack = new Card*[capacity];
		for (int i = 0; i < size; ++i) {
			stack[i] = new Card (*rhs.stack[i]);
		}
	}
	return *this;
}

ostream& operator<<(ostream& output, const Stack& currentStack) {
	int sizeOfStack = currentStack.size;
	for (int i = sizeOfStack - 1; i >= 0; --i) {
		output << *currentStack.stack[i] << "\n";
	}
	return output;
}