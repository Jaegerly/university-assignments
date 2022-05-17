/* CSCI251ProjThree.cpp */

#include <iostream>
#include <string>

#include "MyHashTable.h"

using namespace std;

void menu(); /* display menu. */

int main() {
  string value;
  string key;

  int choice;

  MyHashTable<string, string> table;

  do {
    menu();
    cout << "Enter your choice: \n";
    cin >> choice;
    switch (choice) {
    case 1:
      cout << "Enter an (Key, Value) pair that you will add to table\n";
      cout << "Separate by white space: ";
      cin >> key;
      cin >> value;
      table.insert(key, value);
	  cout << "(" << key << ", " << value << ") entered.\n";
      break;
    case 2:
      cout << "Enter a key that you will remvoe from table: \n";
      cin >> key;
      value = table.remove(key);
      if (!value.empty())
        cout << "Remove successfully. The removed value is " << value << '\n';
      else
        cout << "No such key in table" << '\n';
      break;
    case 3:
      cout << "Enter the key that you want to search for: ";
      cin >> key;
      value = table.get(key);
      if (value.empty())
        cout << "No such data in table\n";
      else
        cout << "The corresponding value is: " << value << endl;
      break;
    case 4:
      if (table.isEmpty())
        cout << "table is empty\n";
      else
        printTable(table);
      break;
    case 5:
      cout << "Make sure you run enough test before you turn it in\n";
      break;
    default:
      cout << "Wrong option. Please choose from menu\n";
      break;
    }
  } while (choice != 5);
}

void menu() {
  cout << "********************************" << endl;
  cout << "*              MENU            *" << endl;
  cout << "* 1. Add a (key, value) pair   *" << endl;
  cout << "* 2. Remove a value by its key *" << endl;
  cout << "* 3. Search a value by its key *" << endl;
  cout << "* 4. Print out table           *" << endl;
  cout << "* 5. Quit                      *" << endl;
  cout << "********************************" << endl;
}