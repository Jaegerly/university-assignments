#include "MyStack.h"

#ifndef MYSTACK_CPP
#define MYSTACK_CPP

template <class T>
MyStack<T>::MyStack() {}

template <class T>
void MyStack<T>::push(T item) {
	v.push_back(item);
}

template <class T>
T MyStack<T>::pop() {
	/* precondition: stack isn't empty. */
	T value = v.back();
	v.pop_back();
	return value;
}

template <class T>
T MyStack<T>::peek() const {
	/* precondition: stack isn't empty. */
	return v.back();
}

template <class T>
int MyStack<T>::size() const {
	return v.size();
}

template <class T>
bool MyStack<T>::isEmpty() const {
	return v.empty();
}

#endif
