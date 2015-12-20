#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

template <class T> 
class Stack {
public:
	Stack ( ) : capacity (13), size (0), stack ( stack = new T*[capacity]) { }

	Stack (int c) : capacity (c), size (0), stack (nullptr) {
		if (c < 0) { capacity = 0; }
		stack = new T*[capacity];
	}

	Stack (const Stack& rhs) : capacity (rhs.capacity), stack (nullptr) {
		stack = new T*[capacity];
		for (size = 0; size < rhs.size; ++size) {
			stack[size] = new T (*rhs.stack[size]);
		}
	}

	~Stack ( ) {
		for (int i = 0; i < size; ++i) {
			delete stack[i];
		}
		delete[] stack;
	}

	int getSize ( ) const {
		return size;
	}

	int getTotalCapacity ( ) const {
		return capacity;
	}

	bool isEmpty ( ) const {
		return size == 0;
	}

	bool isFull ( ) const {
		return size == capacity;
	}

	T* peek ( ) const {
		return stack[size - 1];
	}

	T* pop ( ) {
		if (! isEmpty ( )) {
			return stack[--size];
		}
		return nullptr;
	}

	void push (T* c) {
		if(!isFull()) {
			stack[size++] = c;
		}
	}

	Stack& operator=(const Stack& rhs) {
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

	friend std::ostream& operator<<(std::ostream& output, const Stack& currentStack) {
		for (int i = 0; i < currentStack.size; ++i) {
			output << *currentStack.stack[i] << "\n";
		}
		return output;
	}

private:
	int capacity;
	int size;
	T** stack;
};

#endif
