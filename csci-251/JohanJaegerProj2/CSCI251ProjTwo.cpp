/*	
	CSCI251ProjTwo.cpp
	ProjectTwoCSCI251

	Created by Hongbiao Zeng - 3/12/19.
	Copyright © 2019 Hongbiao Zeng. All Rights Reserved.
*/

#include <iostream>
#include <string>
#include <cctype>

#include "MyStack.h"
#include "MyQueue.h"

using namespace std;

bool isPalindrome(string sentence);

int main(){	
    string sentence;
    char choice;
	
    do {
        cout <<"enter a sentence: ";
        getline(cin, sentence);
        cout << "\"" << sentence << "\"";
        if(isPalindrome(sentence))
            cout << " is a palindrome." << endl;
        else
            cout << " is not a palindrome." << endl;
        cout << "do you want to check another sentence? (y/n): ";
        cin >> choice; /* get response */
        cin.ignore(); /* ignore new lines */
    } while(choice == 'y' || choice == 'Y');
    
	cout << "thanks for testing!\n";
    return 0;
}

bool isPalindrome(string sentence){
    /* algorithm: */
	/* 1. add every character to stack. */
	/* 2. iterate through sentence again, comparing every character with element from stack. */
	/* 3. if they compare, return true. */
	/* 4. otherwise, return false. */

	MyStack<char> reversed;
	
	for (char character: sentence)
		reversed.push(character);

	for (char character: sentence) {
		char comparison = reversed.pop();
		if (character != comparison)
			return false;
	}

	return true;
}