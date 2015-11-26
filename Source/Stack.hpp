#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

#include "Card.hpp"

class Stack {
public:
	Stack ( );

	Stack (int c);

	Stack (const Stack& rhs);

	~Stack ( );

	int getSize ( ) const;

	int getTotalCapacity ( ) const;

	bool isEmpty ( ) const;

	bool isFull ( ) const;

	Card* peek ( ) const;

	Card* pop ( );

	void push (Card* c);

	Stack& operator=(const Stack& rhs);

	friend std::ostream& operator<<(std::ostream& output, const Stack& currentStack);

private:
	int capacity;
	int size;
	Card** stack;
};

#endif