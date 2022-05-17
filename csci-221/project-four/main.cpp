#include <iostream>
#include <assert.h>

#include "JaegerJMoney.h"

using namespace std;

int main() {
	Money first(3);
	Money second(1);

	assert(first.getValue() == 3.0);
	assert(second.getValue() == 1.0);

	Money sum = first + second;
	assert(sum.getValue() == 4.0);

	Money difference = first - second;
	assert(difference.getValue() == 2.0);
	
	Money negation = -first;
	assert(negation.getValue() == -3.0);

	bool negcomparison = (first == second);
	assert(negcomparison == false);

	Money third(3);
	bool poscomparison = (first == third);
	assert(poscomparison == true);

	assert((first < second) == false);
	assert((first <= second) == false);
	assert((first > second) == true);
	assert((first >= second) == true);

	assert((second < first) == true);
	assert((second <= first) == true);
	assert((second > first) == false);
	assert((second >= first) == false);

	Money fourth = first.percent(35);
	assert(fourth.getValue() == 1.05);

	cout << "testing insertion operator. input '-$10.05':\n";
	cin >> third;
	assert(third.getValue() == -10.05);
	cout << "insertion operator works as expected.\n\n";
	
	Money fifth(-35, 21);
	cout << "testing the extraction operator. should print out '- $35.21':\n";
	cout << fifth << '\n';
	cout << "you must decide if output was correct. if it is, the extraction operator works properly.\n";

	return 0;
}