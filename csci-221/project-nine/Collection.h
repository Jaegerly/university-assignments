#ifndef COLLECTION_H
#define COLLECTION_H

#include "Book.h"
using BookClass::Book;

#include <vector>
using std::vector;

namespace CollectionClass {
	class Collection {
		public:
			Collection();

			void add(const Book& novelty);
			Book get(string title);

			void print();
		private:
			vector<Book> Library;
	};
}

#endif