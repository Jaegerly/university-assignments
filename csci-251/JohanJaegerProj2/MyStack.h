#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class MyStack {
public:
    MyStack();
    void push(T item);
    T pop();

    T peek() const;
    int size() const;
    bool isEmpty() const;

private:
    vector<T> v; /* implementation of stack. */
};

#include "MyStack.cpp"
#endif