#ifndef COLLECTION_CPP
#define COLLECTION_CPP

#include "Collection.h"

#include <algorithm>

#include <iostream>
using std::cout;

namespace CollectionClass {
	Collection::Collection() {}

	void Collection::add(const Book& novelty) {
		Library.push_back(novelty);
		sort(Library.begin(), Library.end());
	}
	
	Book Collection::get(string title) {
		/* return copy of book if found in collection. */
		for (auto piece : Library) {
			if (piece.get("title") == title)
				return piece;
		}

		/* otherwise return copy of empty book. */
		Book empty("empty", "empty", "empty");
		return empty;
	}

	void Collection::print() {
		if (Library.size() != 0) {
			cout << "\nthe books entered so far, sorted lexicographically by author are:\n";
		
			for (auto piece : Library) {
				cout << '\t' << piece.get("author") << ". ";
				cout << piece.get("title") << ". ";
				cout << piece.get("date") << ".\n";
			}
		}
		
		else
			cout << "\nno books have been added yet.\n";
	}
}

#endif