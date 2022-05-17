/* This program compares the following four sort algorithms:
 * mergesort, quick sort, select sort, and insert sort
 * Author: Johan Jaeger
 * Date: 1/19/22
 */

#include <algorithm>   // Provides swap
#include <cstdlib>     // Provides EXIT_SUCCESS, size_t
#include <iostream>    // Provides cout
#include <ctime>       // provides clock function.

using namespace std;
const size_t ARRAY_SIZE = 10000; 

// PROTOTYPES of the sorting functions used in this test program:
// Each of these functions has the same precondition and postcondition:
// Precondition: data is an array with at least n components.
// Postcondition: The elements of data have been rearranged so
// that data[0] <= data[1] <= ... <= data[n-1].
void mergesort(int data[ ], size_t n);
void quicksort(int data[], size_t n);
void selectionsort(int data[ ], size_t n);
void insertionsort(int data[], size_t n);

// PROTOTYPE of a function that will test one of the sorting functions:
void testsort(void sorter(int data[], size_t n), const char* name);


int main( )
{
	cout << "This program will generate arrays with ARRAY_SIZE elements" <<endl;
	cout << "Then it sorts the arrays by using different sort function and " << endl;
	cout << "displays the needed time for each sorting\n" << endl;
	cout << "Press Enter key to start test ";
	getchar();
	cout << endl;

    testsort(mergesort,     "mergesort"    );
	cout << "Press Enter key to continue ";
	getchar();
	cout << endl;

    testsort(quicksort,     "quicksort"    );
	cout << "Press Enter key to continue ";
	getchar();
	cout << endl;

    testsort(selectionsort, "selectionsort");
	cout << "Press Enter key to continue ";
	getchar();
	cout << endl;


	testsort(insertionsort, "insertionsort");

	cout << "Press Enter key to exit ";
	getchar();

    return EXIT_SUCCESS;
}



void testsort(void sorter(int data[], size_t n), const char* name)
{
    const int    LIMIT      = 10000;    // Biggest number to put in the array
    int data[ARRAY_SIZE];              // Array of integers to be sorted
    size_t count[LIMIT];               // Count of how many times each
                                       // number appears in data array
    size_t i;                          // Index for the data array.

	clock_t beginning, ending;          // the beginning and ending time to call sorter function

    cout << "Testing the " << name << endl;
    
    // Initialize the count array to zeros:
    fill_n(count, LIMIT, (size_t)0);

    // Fill the data array with random numbers:
    srand(0);
    for (i = 0; i < ARRAY_SIZE; ++i)
    {
	data[i] = rand( ) % (LIMIT);
        ++count[data[i]];
    }
    
    // Sort the numbers
	beginning = clock();
    sorter(data, ARRAY_SIZE);
	ending = clock();

    // Check that the data array is sorted and that it has the right
    // number of copies of each number:
    --count[data[0]];
    for (i = 1; i < ARRAY_SIZE; ++i)
    {
	if (data[i-1] > data[i])
	{
	    cout << "Incorrect sort at index " << i << endl;
	    return;
	}
	--count[data[i]];
    }
    
    for (i = 0; i < (size_t) LIMIT; ++i)
    {
	if (count[i] != 0)
	{
	    cout << "Incorrect numbers in the data array after sorting."
		 << endl;
	    return;
	}
    }


    cout << "Sorting completed correctly ";
	cout << "in " << (ending - beginning)/1000.0 << " seconds\n" << endl;
}


//*************************************************************************
// MERGESORT IMPLEMENTATION:
//

void merge(int data[], size_t first_size, size_t second_size) {
   size_t first_iter = 0, second_iter = 0, merge_iter = 0;
   size_t size = first_size + second_size; /* size of array */

   int merge[size]; /* copy of array, used to merge partitions. */

   while (first_iter < first_size && second_iter < second_size) { /* while both partitions aren't empty */
	   if (data[first_iter] <= data[first_size + second_iter]) { /* append smallest from current pair to "merge". */
		   merge[merge_iter] = data[first_iter];
		   ++first_iter;
	   }

	   else {
		   merge[merge_iter] = data[first_size + second_iter];
		   ++second_iter;
	   }

		++merge_iter;
   }

   while (first_iter < first_size) { /* if first partition still holds elements, loop. */
		merge[merge_iter] = data[first_iter];
		++first_iter;
		++merge_iter;
   }

   while (second_iter < second_size) { /* else, second partition is empty - loop. */
		merge[merge_iter] = data[first_size + second_iter];
		++second_iter;
		++merge_iter;
   }
   
   for (size_t i = 0; i < size; ++i)
	   data[i] = merge[i];
}

void mergesort(int data[], size_t n) {
	/* check for empty condition & a partition of one element. */
	if (n == 0 || n == 1) 
		return;

	size_t midpoint = (n - 1) / 2;
	size_t first_size = midpoint + 1;
	size_t second_size = n - first_size;

	int first[first_size]; /* array for first partition. */
	int second[second_size]; /* array for second partition. */

	/* replete partitions. */
	for (size_t i = 0; i < first_size; ++i)
		first[i] = data[i];

	for (size_t i = 0; i < second_size; ++i)
		second[i] = data[midpoint + i + 1];

	/* mergesort both partitions. */
	mergesort(first, first_size); 
	mergesort(second, second_size); 

	/* update "data" array to reflect partitions. */
	for (size_t i = 0; i < first_size; ++i)
		data[i] = first[i];

	for (size_t i = 0; i < second_size; ++i)
		data[first_size + i] = second[i];

	/* once "data" array updated, merge partitions. */
	merge(data, first_size, second_size);
}

//*************************************************************************



//*************************************************************************
// QUICKSORT IMPLEMENTATION:
//
//*************************************************************************

size_t partition(int data[], size_t n) {
	size_t midpoint = (n / 2) - 1; /* index of midpoint. */
	int pivot = data[midpoint];

	int low = 0, high = n - 1; /* set bounds at first and last elements of container. */
	bool done = false;

	while (!done) {
		while (data[low] < pivot) /* keep moving lower bound up until element that belongs to other side is found. */
			++low;

		while (data[high] > pivot) /* keep moving upper bound down until element that belongs to other side is found. */
			--high;

		if (low >= high) /* if swaps cannot be made because bounds point to same element or have crossed each other. */
			done = true;

		else { /* else, swaps can still be made. */
			int temp = data[low];
			data[low] = data[high];
			data[high] = temp;

			++low;
			--high;
		}
	}

	return high;
}

void quicksort(int data[], size_t n) {
	/* check for empty condition & a partition of one element. */
	if (n == 0 || n == 1)
		return;

	int upper = partition(data, n); /* index of last element in first partition. */

	/* size for partitions. */
	int first_size = upper + 1;
	int second_size = n - first_size;

	int first[first_size];
	int second[second_size];

	/* replete partitions. */
	for (int i = 0; i < first_size; ++i)
		first[i] = data[i];

	for (int i = 0; i < second_size; ++i)
		second[i] = data[first_size + i];

	/* quicksort each partition. */
	quicksort(first, first_size);
	quicksort(second, second_size);

	/* update "data" array to reflect sorted partitions. */
	for (int i = 0; i < first_size; ++i)
		data[i] = first[i];

	for (int i = 0; i < second_size; ++i)
		data[first_size + i] = second[i];
}

//*************************************************************************
// SELECTIONSORT IMPLEMENTATION:
//
void selectionsort(int data[], size_t n) {
  for (size_t i = 0; i < n - 1; ++i) {
	  int tiniest = i; /* standard to compare with every scan. */

	  for (size_t j = i + 1; j < n; ++j) { /* scan for elements smaller than standard. */
		  if (data[j] < data[tiniest])
		  	tiniest = j;
	  }

	  if (tiniest != i) { /* if smaller element is found, swap. */
		int temp = data[i];
		data[i] = data[tiniest];
		data[tiniest] = temp;
	  }
  }
}

//*************************************************************************

//*************************************************************************
// INSERTION SORT IMPLEMENTATION
//
void insertionsort(int data[], size_t n) {
	for (int i = 1; i < n; ++i) {
		int j = i;

		while (j > 0 && data[j] < data[j - 1]) {
			int temp = data[j - 1];
			data[j - 1] = data[j];
			data[j] = temp;
			--j;
		}
	}
}