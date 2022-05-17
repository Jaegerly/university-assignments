#include "MyQueue.h"

#ifndef MYQUEUE_CPP
#define MYQUEUE_CPP

template <class T>
MyQueue<T>::MyQueue() {}

template <class T>
T MyQueue<T>::pop() {
	/* precondition: queue isn't empty. */
	T value = q.front();
	q.pop_front();
	return value;
}

template <class T>
void MyQueue<T>::push(T item) {
	q.push_back(item);
}

template <class T>
T MyQueue<T>::peek() const {
	/* precondition: queue isn't empty. */	
	return q.front();
}

template <class T>
int MyQueue<T>::size() const {
	return q.size();
}

template <class T>
bool MyQueue<T>::isEmpty() const {
	return q.empty();
}

#endif