#include <iostream>
#include <cmath>

#include "JaegerJMoney.h"

/* helper function used for overloaded operator ">>": */
namespace {
	int digitToInt(char c) {
		return (static_cast<int>(c) - static_cast<int>('0'));
	}
}

Money operator +(const Money& amount1, const Money& amount2) {
	Money temp;
	temp.allCents = amount1.allCents + amount2.allCents;
	return temp;
}

Money operator -(const Money& amount1, const Money& amount2) {
	Money temp;
	temp.allCents = amount1.allCents - amount2.allCents;
	return temp;
}

Money operator -(const Money& amount1) {
	Money temp;
	temp.allCents = -amount1.allCents;
	return temp;
}

bool operator ==(const Money& amount1, const Money& amount2) {
	return (amount1.allCents == amount2.allCents);
}

bool operator <(const Money& amount1, const Money& amount2) {
	return (amount1.allCents < amount2.allCents);
}

bool operator <=(const Money& amount1, const Money& amount2) {
	return (amount1.allCents <= amount2.allCents);
}

bool operator >(const Money& amount1, const Money& amount2) {
	return (amount1.allCents > amount2.allCents);
}

bool operator >=(const Money& amount1, const Money& amount2) {
	return (amount1.allCents >= amount2.allCents);
}

Money::Money(long dollars, int cents) {
	bool conditions[] = {(dollars > 0 && cents < 0), (dollars < 0 && cents > 0)};
	/* first condition: dollars are positive and cents are negative. */
	/* second condition: dollars are negative and cents are positive. */ 

	if (conditions[0]) {
		cout << "error: cents can't be negative.\n";
		exit(1);
	}
	else if (conditions[1])
		allCents = dollars * 100 - cents;
	else {
		/* when dollars and cents are both positive or negative. */
		allCents = dollars * 100 + cents;
	}
}

Money::Money(long dollars):allCents(dollars * 100) {}
Money::Money():allCents(0) {}

double Money::getValue() const {
	return (allCents * 0.01);
}

Money Money::percent(int percentFigure) const {
	/* get percentage in cent form. */
	const long amount = allCents * percentFigure / 100;
	
	/* split percentage into dollars and cents. */
	const long dollars = trunc(amount / 100);
	const int cents = amount - (dollars * 100);

	return Money(dollars, cents);
}

istream& operator >>(istream& ins, Money& amount) {
	char oneChar, decimalPoint, digit1, digit2;
	/* digit1 and digit2 specify the amount of cents. */
	long dollars;
	int cents;
	bool negative;

	ins >> oneChar;
	if (oneChar == '-') {
		negative = true;
		/* another prompt to read '$'. */
		ins >> oneChar;
	}
	else {
		negative = false;
	}

	/* if input is legal, oneChar == '$'. */
	ins >> dollars >> decimalPoint >> digit1 >> digit2;

	if (oneChar != '$' || decimalPoint != '.' || !isdigit(digit1) || !isdigit(digit2)) {
		cout << "error: illegal form for input\n";
		exit(1);
	}

	cents = digitToInt(digit1) * 10 + digitToInt(digit2);
	amount.allCents = dollars * 100 + cents;

	if (negative)
		amount.allCents = -amount.allCents;

	return ins;
}

ostream& operator <<(ostream& outs, const Money& amount) {
	long positiveCents, dollars, cents;

	positiveCents = labs(amount.allCents);
	dollars = positiveCents / 100;
	cents = positiveCents % 100;

	if (amount.allCents < 0)
		outs << "- $" << dollars << '.';
	else
		outs << "$" << dollars << '.';

	if (cents < 10)
		outs << '0';

	outs << cents;

	return outs;
}