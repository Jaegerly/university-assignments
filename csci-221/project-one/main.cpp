/* This program requires the student to write 3 functions described in
 * Program project 4 (Page 535) and Program Project 6 (Page 536).
 * The student also need to add a print function to print out an array.
 * The student may watch video notes on MyProgrammingLab to get the idea
 * on how to write the main function and three of these four functions
 *
 * Author: Johan Jaeger
 * Version: 08.26.21
 */

#include <iostream>
#include <string>
#include <string.h>
#include <assert.h>
#include <cstdlib>

using namespace std;

void reverse(char* front, char* rear);

string* addEntry(string* dynamicArray, int& size, string newEntry);
string* deleteEntry(string* dynamicArray, int& size, string entryToDelete);

void print(const string* dynamicArray, int size);

int main()
{
	cout << endl;
	cout << "please see code to view actual tests for 'reverse.' they consist of assert statements." << endl;
	cout << endl;

	/* test one: reverse even string "banana" with 'reverse' function. */
	char first[] = "banana"; // pointer for first parameter in 'reverse.'
	char * last = &(first[strlen(first) - 1]); // 'last' pointer represents the location of the last character in "banana."

	reverse(first, last);
	assert(strcmp(first, "ananab") == 0);

	cout << "test for 'reverse' was successful: \"banana\" to \"ananab\"" << endl;

	/* test two: reverse odd string "automobiles" with 'reverse' function. */
	char second[] = "automobiles"; // pointer for first parameter in 'reverse.'
	last = &(second[strlen(second) - 1]); // 'last' pointer represents the location of the last character in "automobiles."

	reverse(second, last);
	assert(strcmp(second, "selibomotua") == 0);

	cout << "test for 'reverse' was successful: \"automobiles\" to \"selibomotua\"" << endl;

	cout << endl;

	/* test three: reverse user input string */
	cout << endl;

	string input;
	cout << "input a word to reverse (max. 99 letters): ";
	cin >> input;

	char modinput[100]; // to hold input string.
	strcpy(modinput, input.c_str()); // copies input string into 'modinput.'
	char * third = modinput; // pointer for first parameter in 'reverse.'
	last = &(modinput[input.size() - 1]); // 'last' pointer represents the location of the last character in 'input.'
	reverse(third, last);

	cout << "reversed string: ";
	
	for (int i = 0; i < input.size(); i++) { // cout the reversed string, while ignoring uninitialized elements.
		cout << modinput[i];
	}

	cout << endl << endl;

	/* set-up for 'addEntry' and 'deleteEntry' tests. */
	int size = 5;

	string * exper = new string[size]; // 'exper' is the array to be modified.
	string * control = new string[size]; // 'control' array reflects the original state of 'exper.'
	
	control[0] = "tomato";
	control[1] = "lettuce";
	control[2] = "cucumber";
	control[3] = "cheese";
	control[4] = "lemon";

	for (int i = 0; i < size; i++) { // initialize the original state of 'exper.'
		exper[i] = control[i];
	}

	cout << endl;
	cout << "original contents of 'exper' array:" << endl;
	print(exper, size);

	/* test one: 'addEntry.' */
	exper = addEntry(exper, size, "hamburger"); // 'addEntry' returns modified array.
	
	for (int i = 0; i < (size - 1); i++) {
		assert(exper[i] == control[i]); // assert that original elements of 'exper' are intact.
	}
	assert(exper[size - 1] == "hamburger"); // assert that new element "hamburger" has been appended to 'exper.'

	cout << "contents of 'exper' array after 'addEntry' call for \"hamburger\":" << endl;
	print(exper, size); // visual representation of 'exper' after 'addEntry' call.


	/* test two: 'deleteEntry' for an entry that exists. */
	exper = deleteEntry(exper, size, "tomato"); // 'deleteEntry' returns modified array.
	
	for (int i = 1; i < (size); i++) {
		assert(exper[i - 1] == control[i]); // assert that original elements of 'exper' are intact, except for "tomato," which should be removed.
	}

	cout << "contents of 'exper' array after 'deleteEntry' call for \"tomato\":" << endl;
	print(exper, size); // visual representation of 'exper' after 'deleteEntry' call.


	/* test three: 'deleteEntry' for an entry that doesn't exist. */
	exper = deleteEntry(exper, size, "beluga"); // 'deleteEntry' returns modified array.
	
	for (int i = 1; i < (size); i++) {
		assert(exper[i - 1] == control[i]); // assert that original elements of 'exper' are intact.
	}

	cout << "contents of 'exper' array after 'deleteEntry' call for (non-existant) \"beluga\" element:" << endl;
	print(exper, size); // visual representation of 'exper' after 'deleteEntry' call.

	return 0;
}

void reverse(char* front, char* rear)
{	int size = strlen(front); // get C-string length.
	int swaps = size / 2; // determine # of swaps needed. if 'size' is odd, 'swaps' is truncated, as the element at the center should be ignored.

	char temp; // declare 'temp' to store a value of type 'char' during swap.
	for (int i = 0; i < (size / 2); i++) {
		//sub-section one: perform swap.
		temp = *front;
		*front = *rear; // 'front' is assigned the value of 'rear.'
		*rear = temp; // 'rear' is assigned the original value of 'front.'

		//sub-section two: move 'front' and 'rear' one step closer to the center.
		front += 1;
		rear -= 1;
	}
}

string* addEntry(string* dynamicArray, int& size, string newEntry)
{	string * mod = new string[size + 1]; // create a new dynamic array that can hold new entry.
	
	for (int i = 0; i < size; i++) { // copy all elements from 'dynamicArray' into new 'mod' array.
		mod[i] = dynamicArray[i];
	}
	mod[size] = newEntry; // append the new entry to 'mod.'

	size++; // increment 'size' to match the length of 'mod' array.
	delete [] dynamicArray; // delete original 'dynamicArray' to recycle memory.

	return mod;
}

string* deleteEntry(string* dynamicArray, int& size, string entryToDelete) // removes first instance of 'entryToDelete.'
{	string * mod = new string[size - 1]; // new dynamic array whose length is one less than the 'size' of 'dynamicArray.'
	bool entryFound = false; // indicates whether 'entryToDelete' was found in 'dynamicArray.'

	for (int i = 0; i < size; i++) {
		if (dynamicArray[i] == entryToDelete && !entryFound) { // if the first instance of 'entryToDelete' is found, update 'entryFound' and proceed.
			entryFound = true;
		}
		else if (entryFound) { // else if 'entryToDelete' has already been found, subtract one from 'i' (since 'entryToDelete' was skipped).
			mod[i - 1] = dynamicArray[i];
		}
		else if (i != (size - 1)) { // else copy 'dynamicArray[i]' into 'mod[i]' if it's not the last element in 'dynamicArray.'
			mod[i] = dynamicArray[i];
		}
	}

	if (entryFound) { // if 'entryToDelete' was found...
		size--; // decrement 'size' to match the length of 'mod' array.
		delete [] dynamicArray; // delete original 'dynamicArray' to recycle memory.

		return mod;
	}
	else { // else if 'entryToDelete' was not found...
		return dynamicArray;
	}
}

void print(const string* dynamicArray, int size) 
{	cout << endl;
	
	for (int i = 0; i < size; i++) { // iterate through 'dynamicArray,' printing every element with its index on a new line.
		cout << dynamicArray[i] << ": " << i << endl;
	}

	cout << endl;
}