#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <list>

using namespace std;

template<class T>
class MyQueue {
public:
    MyQueue();
    T pop();
    void push(T item);

    T peek() const;
    int size() const;
    bool isEmpty() const;

private:
    list<T> q; /* implementation of queue. */
};

#include "MyQueue.cpp"
#endif