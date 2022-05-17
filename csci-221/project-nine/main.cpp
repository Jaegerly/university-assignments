#include "Collection.h"
using CollectionClass::Collection;

#include <iostream>
using std::cout;
using std::cin;

#include <assert.h>

int main() {
  cout << "section one: testing book class\n";

  cout << "\ntesting constructor...\n";

  Book Bible("Bible", "40ish Authors", "100's Of Years");
  Book Textbook("Learning C++", "Walter Savitch", "2019");
  
  cout << "complete.\n";

  cout << "\ntesting accessor methods...\n";
 
  assert(Bible.get("title") == "Bible");
  assert(Bible.get("author") == "40ish Authors");
  assert(Bible.get("date") == "100's Of Years");

  assert(Textbook.get("title") == "Learning C++");
  assert(Textbook.get("author") == "Walter Savitch");
  assert(Textbook.get("date") == "2019");

  cout << "complete.\n";

  cout << "\ntesting setter methods...\n";

  Bible.set("title", "Scripture");
  assert(Bible.get("title") == "Scripture");

  Bible.set("author", "Holy Spirit");
  assert(Bible.get("author") == "Holy Spirit");

  Bible.set("date", "1100 years");
  assert(Bible.get("date") == "1100 years");

  Textbook.set("title", "Problem-Solving w/ C++");
  assert(Textbook.get("title") == "Problem-Solving w/ C++");

  Textbook.set("author", "Gene Bryant");
  assert(Textbook.get("author") == "Gene Bryant");

  Textbook.set("date", "2021");
  assert(Textbook.get("date") == "2021");

  cout << "complete.\n";

  cout << "\ntesting < operator...\n";

  assert(Textbook < Bible);
  Book Leadership("Leaders Eat Last", "Simon Sinek", "2017");
  Book Business("The Innovation Dilemma", "Clayton M. Christensen", "2005");

  assert(Business < Leadership);
  assert(Textbook < Leadership);
  assert(Business < Bible);

  cout << "complete.\n";

  cout << "\ntesting == operator...\n";

  Book Math("Math 5", "Judy Howe", "2004");
  Book Mathematics("Math 5", "Judy Howe", "2004");

  assert(Math == Mathematics);

  Book Calculus("Calculus I", "Adam Heck", "2019");
  Book Math121("Calculus I", "Adam Heck", "2019");

  assert(Calculus == Math121);

  cout << "complete.\n";

  cout << "\nsection two: testing collection class\n";

  cout << "\ntesting constructor...\n";

  Collection Bookcase;

  cout << "testing complete.\n";

  cout << "\ntesting add method...\n";

  Bookcase.add(Bible);
  assert(Bookcase.get("Scripture") == Bible);

  Bookcase.add(Textbook);
  assert(Bookcase.get("Problem-Solving w/ C++") == Textbook);
  
  Bookcase.add(Leadership);
  assert(Bookcase.get("Leaders Eat Last") == Leadership);
  
  Bookcase.add(Business);
  assert(Bookcase.get("The Innovation Dilemma") == Business);

  cout << "testing complete.\n";

  Collection UserCollection;

  while (true) {
	cout << "\nselect from the following choices:\n";
	cout << "\t 1. add new book to library\n";
	cout << "\t 2. print books sorted by author\n";
	cout << "\t 3. quit\n\n";

	char response;
	cin >> response;

	char next;

	do {
		cin.get(next);
	} while (next != '\n');

	if (response == '3')
		break;
	
	cout << '\n';

	if (response == '1') {
		string title, author, date;

		cout << "enter title:\n";
		getline(cin, title);

		cout << "\nenter author:\n";
		getline(cin, author);

		cout << "\nenter date:\n";
		getline(cin, date);

		cout << '\n';

		Book addition(title, author, date);
		UserCollection.add(addition);
	}

	if (response == '2') 
		UserCollection.print();
  }
} 