/* Do Programming Project 2 on page 611. You may watch the video note for 
 * Programming Project 1 on page 611 to get some idea. Then try to finish
 * independently by complete this sample file.
 * 
 * Author: Johan Jaeger
 * Version: 09.08.21
 */

#include <iostream>
#include <assert.h>

using namespace std;

class CDAccount {
	public:
		CDAccount();
		CDAccount(double new_balance, double new_interest_rate, int new_term);
		
		double get_initial_balance() const;
		double get_balance_at_maturity() const;
		double get_interest_rate() const;
		int get_term() const;

		void input(istream& in);
		void output(ostream& out);
		
	private:
		void balance_breakup(double money);

		int dollar;
		int cent;
		double interest_rate;
		int term; // months until maturity
};

int main() {
	cout << endl;

	/* section one: testing accessors with default constructor... */ 
	cout << "section one: testing accessors with default constructor" << endl;

	cout << endl;

	CDAccount account; // default constructor called

	cout << "account.get_initial_balance() == 0.0: "; // test for get_initial_balance()
	assert(account.get_initial_balance() == 0.0);
	cout << "passed" << endl;

	cout << endl;

	cout << "account.get_balance_at_maturity() == 0.0: "; // test for get_balance_at_maturity()
	assert(account.get_balance_at_maturity() == 0.0);
	cout << "passed" << endl;

	cout << endl;

	cout << "account.get_interest_rate() == 0.0: "; // test for get_interest_rate()
	assert(account.get_interest_rate() == 0.0);
	cout << "passed" << endl;

	cout << endl;

	cout << "account.get_term() == 0: "; // test for get_term()
	assert(account.get_term() == 0);
	cout << "passed" << endl;

	cout << endl << endl << endl;

	/* section two: testing accessors with non-default constructor... */ 
	cout << "section two: testing accessors with non-default constructor" << endl;

	cout << endl;

	account = CDAccount(12.52, 5.5, 8);

	cout << "account.get_initial_balance() - 12.52 <= 0.1: "; // // test for get_initial_balance(). since using the equality operator with "double" values is unreliable, this test uses an inequality.
	assert(account.get_initial_balance() - 12.52 <= 0.1);
	cout << "passed" << endl;

	cout << endl;

	cout << "account.get_balance_at_maturity() - 12.9 <= 0.1: "; // test for get_balance_at_maturity(). since using the equality operator with "double" values is unreliable, this test uses an inequality.
	assert(account.get_balance_at_maturity() - 12.9 <= 0.1);
	cout << "passed" << endl;

	cout << endl;

	cout << "account.get_interest_rate() - 0.055 <= 0.1: "; // test for get_interest_rate(). since using the equality operator with "double" values is unreliable, this test uses an inequality.
	assert(account.get_interest_rate() - 0.055 <= 0.1);
	cout << "passed" << endl;

	cout << endl;

	cout << "account.get_term() == 8: "; // test for get_term()
	assert(account.get_term() == 8);
	cout << "passed" << endl;

	cout << endl << endl << endl;

	/* section three: (manually) testing input and output functions */ 
	cout << "section three: (manually) testing input and output functions" << endl;

	cout << endl;

	account.input(cin);
	cout << endl;
	account.output(cout);
}

CDAccount::CDAccount(): dollar(0), cent(0), interest_rate(0.0), term(0) {
	// set all member variables to "0" or "0.0".
}

CDAccount::CDAccount(double new_balance, double new_interest_rate, int new_term): term(new_term){
    balance_breakup(new_balance); // break up "new_balance" into two "int" values for "dollar" and "cent"
	interest_rate = new_interest_rate / 100; // convert "new_interest_rate" into decimal (e.g. 4.3% -> 0.043)
}

double CDAccount::get_initial_balance() const {
	return dollar + (cent / (double) 100); // return initial balance as a double
}

double CDAccount::get_balance_at_maturity() const {
	double initial_balance = get_initial_balance(); // get initial balance as a double
	double interest = initial_balance * interest_rate * (term / 12.0); // calculate interest based on "initial_balance," "interest_rate," and "term"

	return initial_balance + interest; // return balance at maturity
}

double CDAccount::get_interest_rate() const {
	return interest_rate; // return "interest_rate" member variable
}

int CDAccount::get_term() const {
	return term; // return "term" member variable
}

void CDAccount::input(istream& in) {
    cout << "please enter balance (e.g., 12.72): ";
	
	double balance;
    in >> balance; // get initial balance from user input
    
    balance_breakup(balance); // break up "balance" into two "int" values for "dollar" and "cent"
    
	cout << endl;
    cout << "please enter interest rate as a percentage (e.g., 5.3): ";

    in >> interest_rate; // get interest rate from user input
	interest_rate = interest_rate / 100.0; // convert "interest_rate" into decimal (e.g. 4.3% -> 0.043)
	
	cout << endl;
    cout << "please enter term as a natural number from 1 to 12 (inclusive): ";

    in >> term; // get term from user input
}

void CDAccount::output(ostream& out) {
	out.setf(ios::fixed); // no scientific notation
	out.setf(ios::showpoint); // always show decimal point
	out.precision(3); // round up to two decimal places

	out << "initial balance: " << get_initial_balance() << endl << endl; // output for "get_initial_balance()"
	out << "interest rate: " << get_interest_rate() << endl << endl; // output for "get_interest_rate()"
	out << "mature balance (i.e. balance in " << get_term() << " months): " << get_balance_at_maturity() << endl << endl; // output for "get_term()" and "get_balance_at_maturity()"
}

void CDAccount::balance_breakup(double money) {
	dollar = (int) money; // integer part of balance
    cent = (int) ((money - dollar) * 100.0); // (decimal part of balance) * 100
}