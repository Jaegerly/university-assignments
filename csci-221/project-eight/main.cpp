#include <iostream>
using std::cout;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>
using std::find;
using std::distance;

#include <assert.h>

/* necessary declarations: */
template <class T>
class set;

/* test functions: */

/* function to print the contents of a vector. */
template <class T>
void printvtr(const vector<T>& a) {
	if (a.size() == 0)
		cout << "vector has no elements.";

	else {
		cout << "vector elements: ";

		for (int i = 0; i < a.size(); ++i)
			cout << a.at(i) << " ";
	}

	cout << "\n";
}

/* friend function to return the size of the private vector. */
/* yes, there is also a "getSize" method in the class, but this */
/* function is meant to test the constructors. thus, we don't want */
/* errors in "getSize" to hide errors in the constructors. */

template <class T>
int vtrSetSize(const set<T>& a) {
	return a.group.size();
}

/* "set" template: */

template <class T>
class set {
	public:
		/* constructors: */
		set();
		set(const vector<T>& a);

		/* friends: */
		friend int vtrSetSize <>(const set<T>& a);
		
		/* member functions: */
		void addItem(const T& item);
		void removeItem(const T& item);

		int search(const T& item) const;
		int getSize() const;

		/* dynamic array generator for set */
		T* genArray() const;

	/* private: */
		bool notin(const vector<T>& a, const T& val) const;
		vector<T> group; 
};

template <class T>
set<T>::set() {}

template <class T>
set<T>::set(const vector<T>& a) {
	for (int i = 0; i < a.size(); ++i) {
		T current = a.at(i);

		if (notin(group, current))
			group.push_back(current);
	}
}

/* helper function: */
template <class T>
bool set<T>::notin(const vector<T>& a, const T& val) const {
	if (find(group.begin(), group.end(), val) == group.end())
		return true;
	return false;
}

template <class T>
void set<T>::addItem(const T& item) {
	try {
		if (notin(group, item))
			group.push_back(item);
		else
			throw 0;
	}

	catch(int error) {
		cout << "item could not be added: " << item << '\n';
	}
}

template <class T>
int set<T>::search(const T& item) const { /* returns the index of item in vector. if non-existent, -1. */
	if (notin(group, item))
		return -1;

	return distance(group.begin(), find(group.begin(), group.end(), item));
}

template <class T>
void set<T>::removeItem(const T& item) {
	try {
		int index = search(item);

		if (index == -1)
			throw 0;

		group.erase(group.begin() + index);
	}
	
	catch(int error) {
		cout << "item could not found: " << item << '\n';
	}
}

template <class T>
int set<T>::getSize() const {
	return group.size();
}

template <class T>
T* set<T>::genArray() const {
	T* headptr = new T[getSize()];

	for (int i = 0; i < getSize(); ++i)
		headptr[i] = group.at(i);

	return headptr;
}

int main() {
	/* tests: */

	/* for default constructor: */
	set<int> empty;
	assert(vtrSetSize(empty) == 0);

	/* for constructor with vector parameter: */
	vector<int> vtr;

	vtr.push_back(10);
	vtr.push_back(15);
	vtr.push_back(28);

	set<int> notempty(vtr);

	assert(vtrSetSize(notempty) == 3);

	/* for "addItem": */
	set<int> addItemSet;
	addItemSet.addItem(3);
	addItemSet.addItem(-1);
	addItemSet.addItem(5);
	addItemSet.addItem(15);
	addItemSet.addItem(0);

	assert(vtrSetSize(addItemSet) == 5);

	cout << "attempting to add duplicate to set:\n";
	addItemSet.addItem(0); /* attempting to add item that's already in set. expect output. */
	assert(vtrSetSize(addItemSet) == 5);
	cout << '\n';

	/* for "removeItem": */
	vector<int> removeItemVtr;
	removeItemVtr.push_back(3);
	removeItemVtr.push_back(4);
	removeItemVtr.push_back(10);

	set<int> removeItemSet(removeItemVtr);
	
	removeItemSet.removeItem(4);
	assert(vtrSetSize(removeItemSet) == 2);

	removeItemSet.removeItem(3);
	assert(vtrSetSize(removeItemSet) == 1);

	cout << "attempting to remove item that doesn't exist in set:\n";
	removeItemSet.removeItem(4); /* attempting to remove item that's already been removed. expect output. */
	assert(vtrSetSize(removeItemSet) == 1);
	cout << '\n';
	
	removeItemSet.removeItem(10);
	assert(vtrSetSize(removeItemSet) == 0);

	cout << "attempting to remove item from empty set:\n";
	removeItemSet.removeItem(10); /* attempting to remove item from empty set. expect output. */
	assert(vtrSetSize(removeItemSet) == 0);
	cout << '\n';

	/* for "getSize": */
	vector<char> getSizeVtr;

	getSizeVtr.push_back('h');
	getSizeVtr.push_back('e');
	getSizeVtr.push_back('r');
	getSizeVtr.push_back('r');
	getSizeVtr.push_back('o');
	getSizeVtr.push_back(' ');
	getSizeVtr.push_back('t');
	getSizeVtr.push_back('h');
	getSizeVtr.push_back('e');
	getSizeVtr.push_back('r');
	getSizeVtr.push_back('e');

	set<char> getSizeSet(getSizeVtr);
	assert(getSizeSet.getSize() == 6); /* since repeating characters aren't allowed. */

	/* for "search": */
	vector<string> searchVtr;
	searchVtr.push_back("first");
	searchVtr.push_back("second");
	searchVtr.push_back("third");
	searchVtr.push_back("fourth");
	searchVtr.push_back("fifth");

	set<string> searchSet(searchVtr);
	assert(searchSet.search("first") == 0);
	assert(searchSet.search("second") == 1);
	assert(searchSet.search("third") == 2);
	assert(searchSet.search("fourth") == 3);
	assert(searchSet.search("fifth") == 4);
	assert(searchSet.search("sixth") == -1);

	/* for "genArray": */
	vector<string> genArrayVtr;
	genArrayVtr.push_back("the truth");
	genArrayVtr.push_back("the false");
	genArrayVtr.push_back("the ugly");

	set<string> genArraySet(genArrayVtr);
	string* dynArray = genArraySet.genArray();

	assert(dynArray[0] == "the truth");
	assert(dynArray[1] == "the false");
	assert(dynArray[2] == "the ugly");

	delete [] dynArray;

	cout <<  "all tests passed :D! most of them are assert statements.\n";
	
  	return 0;
} 