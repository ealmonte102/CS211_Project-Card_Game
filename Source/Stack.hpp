#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

template <class T> 
class Stack {
public:
	Stack ( );

	Stack(int c);

	Stack(const Stack& rhs);

	Stack& operator=(const Stack& rhs);

	~Stack( );

	int getSize( ) const;

	int getTotalCapacity( ) const;

	bool isEmpty( ) const;

	bool isFull( ) const;

	T* peek( ) const;

	T* pop( );

	void push(T* c);

	friend std::ostream& operator<<(std::ostream& output, const Stack& currentStack) {
		for (int i = currentStack.size - 1; i >= 0; --i) {
			output << *currentStack.stack[i] << "\n";
		}
		return output;
	}

private:
	int capacity;
	int size;
	T** stack;
};


template <class T>
Stack<T>::Stack ( ) : capacity (13), size (0), stack (stack = new T*[capacity]) { }

template <class T>
Stack<T>::Stack(int c): capacity (c), size (0), stack (nullptr) {
	if (c < 0) { capacity = 0; }
	stack = new T*[capacity];
}

template <class T>
Stack<T>::Stack(const Stack& rhs): capacity (rhs.capacity), stack (nullptr) {
	stack = new T*[capacity];
	for (size = 0; size < rhs.size; ++size) {
		stack[size] = new T (*rhs.stack[size]);
	}
}

template <class T>
Stack<T>::~Stack( ) {
	for (int i = 0; i < size; ++i) {
		delete stack[i];
	}
	delete[] stack;
}

template <class T>
int Stack<T>::getSize( ) const {
	return size;
}

template <class T>
int Stack<T>::getTotalCapacity( ) const {
	return capacity;
}

template <class T>
bool Stack<T>::isEmpty( ) const {
	return size == 0;
}

template <class T>
bool Stack<T>::isFull( ) const {
	return size == capacity;
}

template <class T>
T* Stack<T>::peek( ) const {
	return stack[size - 1];
}

template <class T>
T* Stack<T>::pop( ) {
	if (! isEmpty ( )) {
		return stack[--size];
	}
	return nullptr;
}

template <class T>
void Stack<T>::push(T* c) {
	if(!isFull()) {
		stack[size++] = c;
	}
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) {
	if (this != &rhs) {
		for (int i = 0; i < size; ++i) {
			delete stack[i];
		}
		delete[] stack;

		capacity = rhs.capacity;
		stack = new T*[capacity];
		for (size = 0; size < rhs.size; ++size) {
			stack[size] = new T (*rhs.stack[size]);
		}
	}
	return *this;
}
#endif
