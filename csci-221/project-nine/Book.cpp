#ifndef BOOK_CPP
#define BOOK_CPP

#include "Book.h"

#include <map>
using std::map;

namespace BookClass {
	Book::Book(string title, string author, string date) {
		group["title"] = title;
		group["author"] = author;
		group["date"] = date;
	}

	void Book::set(string attr, string value) {
		map<string, bool> dictionary;

		dictionary["author"] = "author" == attr;
		dictionary["title"] = "title" == attr;
		dictionary["date"] = "date" == attr;

		for (auto pair : dictionary) {
			if (pair.second == true) {
				group[pair.first] = value;
				break;
			}
		}
	}
	
	string Book::get(string attr) {
		return group[attr];
	}

	bool Book::operator < (Book& compare) {
		return group["author"] < compare.get("author");
	}

	bool Book::operator == (Book& compare) {
		return (group["title"] == compare.get("title")) &&
			   (group["author"] == compare.get("author"));
	}
}

#endif