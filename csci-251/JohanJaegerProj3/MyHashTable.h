/* MyHashTable.h */

#include <iostream>
using namespace std;

#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

template<class K, class V>
struct MyHashEntry { /* node belonging to singly linked list. */
    K key;
    V value;
    MyHashEntry* next;
};

template<class K, class V>
class MyHashTable { /* one bucket per element. use linear-ordering. */
	public:
	    template<class E, class T>
	    friend void printTable(MyHashTable<E, T> table);

	    MyHashTable(); /* default size = 10 buckets */
	    MyHashTable(int table_size); /* size = number of buckets. */

	    int size() const; /* returns number of filled buckets in table. */
	    V get(K key) const; /* returns the element with given key, if it exists. */
	    void insert(K key, V value); /* insert (key, value) element in table. */
	    V remove(K key); /* pop element with key. */
	    bool isEmpty() const; /* return true if there are no filled buckets. */
	
	private:
	    MyHashEntry<K, V>** table; /* head of array. */
	    int count; /* number of filled buckets in table.*/
	    int numOfBuckets;

		void resize(); /* helper function to resize table. for more organized code. */
};

/* implementations: */

template<class K, class V>
MyHashTable<K, V>::MyHashTable(): numOfBuckets(10), count(0) {
	table = new MyHashEntry<K, V>*[10]; /* a dynamic array with pointers to entries. */

	for (int i = 0; i < 10; ++i) /* default value for buckets. */
		table[i] = nullptr;
}

template<class K, class V>
MyHashTable<K, V>::MyHashTable(int table_size): numOfBuckets(table_size), count(0) {
	table = new MyHashEntry<K, V>*[table_size]; /* a dynamic array with pointers to entries. */

	for (int i = 0; i < table_size; ++i) /* default value for buckets. */
		table[i] = nullptr;
}

template<class K, class V>
int MyHashTable<K, V>::size() const {
	return count;
}

int hasher(string key, int size) { /* helper function for reusable hashing. */
	int sum = 0; /* hold sum of key's ASCII encodings. */

	for (char character: key)
		sum += character;
	
	return sum % size; /* determine bucket for key. */
}

template<class K, class V>
void MyHashTable<K, V>::resize() {	
	int newSize = numOfBuckets * 2; /* new size of table. */
	
	MyHashEntry<K, V>** copy = new MyHashEntry<K, V>*[numOfBuckets]; /* copy original table. */

	for (int i = 0; i < numOfBuckets; ++i)
		copy[i] = &(*(table[i])); /* dereference address of MyHashEntries. */

	table = new MyHashEntry<K, V>*[newSize]; /* resize original table. all values in table are wiped. */
		
	for (int i = 0; i < newSize; ++i) { /* insert every original element in resized table. */
		if (i >= numOfBuckets || copy[i] == nullptr)
			table[i] = nullptr;
		else {
			K key = (copy[i]) -> key;
			V value = (copy[i]) -> value;
			
			insert(key, value);
		}
	}

	numOfBuckets = newSize;
}

template<class K, class V>
void MyHashTable<K, V>::insert(K key, V value) {
	int bucket = hasher(key, numOfBuckets); /* original mapped bucket. */
	
	/* cout << "mapped bucket: " << bucket << '\n'; */
	
	int i = 0;
	while (i < numOfBuckets) {
		int index = (bucket + i) % numOfBuckets; /* adding i enables linear ordering. */
		
		if (table[index] == nullptr) { /* if bucket is empty, insert element. */
			table[index] = new MyHashEntry<K, V>{key, value};
			++count; /* increment count. */
			return;
		}

		++i;
	}

	resize(); /* if no empty bucket in container, resize it. */
	insert(key, value); /* the insertion should work now. */
}

template<class K, class V>
V MyHashTable<K, V>::get(K key) const {
	int bucket = hasher(key, numOfBuckets); /* original mapped bucket. */

	int i = 0;
	while (i < numOfBuckets) {
		int index = (bucket + i) % numOfBuckets; /* determine offset from bucket each iteration. */
		
		if (table[index] != nullptr && key == (table[index]) -> key) /* linear search through hash table. */
			return (table[index]) -> value;

		++i;
	}

	return ""; /* if element not found, return empty string. */
}

template<class K, class V>
V MyHashTable<K, V>::remove(K key) {
	int bucket = hasher(key, numOfBuckets); /* original mapped bucket. */

	int i = 0;
	while (i < numOfBuckets) {
		int index = (bucket + i) % numOfBuckets; /* starting bucket. */
		
		if (table[index] != nullptr && key == (table[index]) -> key) { /* linear search through hash table. */
			V value = (table[index]) -> value; /* store value of element to be removed. */
			
			table[index] = nullptr; /* make bucket empty. */
			--count; /* decrement count. */
			
			return value; /* return value of element. */
		}
			
		++i;
	}

	return ""; /* if element not found, return empty string. */
}

template<class K, class V>
bool MyHashTable<K, V>::isEmpty() const {
	return count == 0;
}

template<class E, class T>
void printTable(MyHashTable<E, T> table) {
	cout << '\n';
	
	for (int i = 0; i < table.numOfBuckets; ++i) {
		if (table.table[i] == nullptr)
			cout << "empty.";
		else
			cout << '(' << (table.table[i]) -> key << ": " << (table.table[i]) -> value << ')';

		cout << '\n';
	}
}

#endif