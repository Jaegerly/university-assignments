#include "CSCI361Proj5.h"

namespace FHSULINKEDLIST {
	size_t list_length(const Node* head_ptr) {
		size_t sum = 0;
		
		if (head_ptr == NULL) {
			return 0;
		}

		/* iterate through the linked list and update "sum" after every iteration. */
		for (const Node* i = head_ptr; i != NULL; i = i -> link)
			++sum;

		return sum;
	}


	void list_head_insert(Node*& head_ptr, const Node::Item& entry) {
		/* create new node */
		
		Node* temp = new Node;
		temp -> data = entry;

		/* insertion for the empty list. */
		
		if (head_ptr == NULL)
			temp -> link = NULL;

		/* insertion for non-empty lists. */

		else
			/* make "temp" point to "head_ptr" */
			temp -> link = head_ptr;

		/* make "head_ptr" point to new node. */
		head_ptr = temp;
	}
	
	void list_insert(Node* previous_ptr, const Node::Item& entry) {
		/* create new node */
		
		Node* temp = new Node;
		temp -> data = entry;

		/* insertion for the empty list. */
		
		if (previous_ptr == NULL) {
			previous_ptr = temp;
		}

		/* insertion for non-empty lists. */
		else {
			/* make "temp" point to what "previous_ptr" points to. */
			temp -> link = previous_ptr -> link;

			/* make "previous_ptr" point to "temp". */
			previous_ptr -> link = temp;
		}
	}

	Node* list_search(Node* head_ptr, const Node::Item& target) {
		/* check for the empty list. */
		
		if (head_ptr == NULL)
			return NULL;

		/* else proceed as usual. */
		else {
			/* iterate through linked list, and if target is found, return its node. */
			
			for (Node* i = head_ptr; i != NULL; i = i -> link) {
				if (i -> data == target)
					return i;
			}

			/* else return "NULL". */
			return NULL;
		}
	}

	Node* list_locate(Node* head_ptr, size_t position) {
		/* check for the empty list. */
		
		if (head_ptr == NULL)
			return NULL;

		/* else proceed as usual. */
		else {
			/* iterate through linked list, and if position exists, return the correponding node. */
			
			size_t posCounter = 0;

			for (Node* i = head_ptr; i != NULL; i = i -> link) {
				++ posCounter;

				if (posCounter == position)
					return i;
			}

			/* else return "NULL". */
			return NULL;
		}
	}

	void list_head_remove(Node*& head_ptr) {
		/* check for the empty list before proceeding. */
		
		if (head_ptr != NULL) {
			/* then proceed to remove *(head_ptr). */
			const Node* temp = head_ptr;
			head_ptr = temp -> link;
			delete temp;
		}
	}

	void list_remove(Node* previous_ptr) {
		/* check for the empty list before proceeding. */

		if (previous_ptr -> link != NULL) {
			const Node* after = previous_ptr -> link;
			previous_ptr -> link = after -> link;
			delete after;
		}
	}

	void list_clear(Node*& head_ptr) {
		/* check for the empty list before proceeding. */
		
		if (head_ptr != NULL) {
			/* iterate through list and delete every node. */

			Node* temp;

			for (Node*& i = head_ptr; i != NULL; i = temp) {
				temp = i -> link;
				delete i;
			}

			/* set "head_ptr" to NULL. */ 
			head_ptr = NULL;
		}
	}

	void list_copy(Node* source_ptr, Node*& head_ptr) {
		/* check for the empty list before proceeding. */
		
		if (head_ptr != NULL) {
			/* "previous" holds the second-to-last node of new linked list. */
			/* "previous" is used to set "link" to the right location. */
			
			Node* previous;
			
			head_ptr -> data = source_ptr -> data;
			head_ptr -> link = NULL;

			previous = head_ptr;

			for (Node* i = source_ptr -> link; i != NULL; i = i -> link) {
				/* create new node */
				
				Node* after = new Node;
				after -> data = i -> data;
				after -> link = NULL;

				/* make "previous" point to "after". */
				previous -> link = after;

				/* set "previous" to "after". */
				previous = after;
			}
		}
	}

	size_t list_occurrences(Node* head_ptr, const Node::Item& target) {
		size_t count = 0;
		
		/* check for the empty list. */
		
		if (head_ptr == NULL)
			return count;

		/* then proceed to iterate through list and count occurences of "target". */

		for (Node* i = head_ptr; i != NULL; i = i -> link) {
			if (i -> data == target)
				++ count;
		}

		return count;
	}

	void list_tail_attach(Node*& head_ptr, const Node::Item& entry) {
		/* create a new node. */
		
		Node* newNode = new Node;
		newNode -> data = entry;
		newNode -> link = NULL;

		/* case for empty list. */
		
		if (head_ptr == NULL)
			head_ptr = newNode;
		
		/* case for non-empty list. */

		else {
			/* then proceed to iterate through list and modify the last node */
			/* to point to "newNode". */

			/* access last node. */

			Node* i;
			Node* last;

			for (i = head_ptr; i != NULL; i = i -> link) {
				if (i -> link == NULL) 
					last = i;
			}

			/* modify last node. */

			last -> link = newNode;
		}
	}

	void list_tail_remove(Node*& head_ptr) {
		if (head_ptr != NULL) {
			Node* i;

			Node* secondToLast = NULL;
			Node* last;

			/* iterate through list and assign nodes to "secondToLast" and "last". */

			for (i = head_ptr; i != NULL; i = i -> link) {
				if (i -> link == NULL)
					last = i;
				else if ((i -> link) -> link == NULL) 
					secondToLast = i;
			}

			/* if "secondToLast" does exist, update it to point to "NULL". */

			if (secondToLast != NULL)
				secondToLast -> link = NULL;

			/* else if there is only one node in the list, point "head_ptr" to "NULL". */

			else
				head_ptr = NULL;
			
			/* delete "last". */

			delete last;
		}
	}

	Node* list_copy_front(Node* source_ptr, size_t n) {
		/* check for empty list. */

		if (source_ptr == NULL)
			return NULL;

		/* else proceed as usual. */

		else { // list contains 1, 2, 3, 4

			/* "previous" holds the second-to-last node of new linked list. */
			/* "previous" is used to set "link" to the right location. */
			
			Node* previous;

			/* creating head pointer for new linked list. */

			Node* head_ptr = new Node;
			
			head_ptr -> data = source_ptr -> data;
			head_ptr -> link = NULL;

			previous = head_ptr;

			/* creating a variable to keep track of the current index. */

			size_t position	= 0;
			
			/* declaring iterator. */
			Node* i;	

			/* iterate through original linked list and copy to new linked list. */
			for (i = source_ptr -> link; (i != NULL) && (position < n - 1); i = i -> link) {
				++ position;

				/* create new node */
				
				Node* after = new Node;
				after -> data = i -> data;
				after -> link = NULL;

				/* make "previous" point to "after". */
				previous -> link = after;

				/* set "previous" to "after". */
				previous = after;
			}

			return head_ptr;
		}
	}
}

