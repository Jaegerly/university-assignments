#ifndef BOOK_H
#define BOOK_H

#include <string>
using std::string;

#include <map>
using std::map;

namespace BookClass {
	class Book {
		public:
			Book(string title, string author, string date);

			/* multi-getters and setters: */
			void set(string attr, string value);
			string get(string attr);

			/* used to order BookClass objects before display: */
			bool operator < (Book& compare);

			/* evaluates to true if both obj.'s have the same content: */
			bool operator == (Book& compare);
		private:
			/* data structure to hold book information: */
			map <string, string> group;
	};
}

#endif