#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>

using namespace std;

#ifndef MONEY_H
#define MONEY_H

/* class for U.S.D. */
class Money {
	public:
		friend Money operator +(const Money& amount1, const Money& amount2);
		/* returns: the sum of "amount1" and "amount2" in the form of a Money object. */

		friend Money operator -(const Money& amount1, const Money& amount2);
		/* returns: the difference of "amount1" and "amount2" in the form of a Money object. */

		friend Money operator -(const Money& amount1);
		/* returns: the negation of "amount1" in the form of a Money object */

		friend bool operator ==(const Money& amount1, const Money& amount2);
		/* returns: the equality of "amount1" and "amount2" in the form of a Boolean. */

		friend bool operator <(const Money& amount1, const Money& amount2);
		/* returns: "true" in the form of a Boolean if "amount1" is less than  "amount2". otherwise, false. */

		friend bool operator <=(const Money& amount1, const Money& amount2);
		/* returns: "true" in the form of a Boolean if "amount1" is less than or equal to "amount2". otherwise, false. */

		friend bool operator >(const Money& amount1, const Money& amount2);
		/* returns: "true" in the form of a Boolean if "amount1" is greater than  "amount2". otherwise, false. */

		friend bool operator >=(const Money& amount1, const Money& amount2);
		/* returns: "true" in the form of a Boolean if "amount1" is greater than or equal to "amount2". otherwise, false. */

		/* constructors: */

		Money(long dollars, int cents);
		/* "dollars" and "cents" can both be negative, "dollars" can be negative alone, but "cents" alone cannot be negative. if "dollars" are negative alone, the constructor assumes that "cents" should also be negative. */

		Money(long dollars);
		Money();

		double getValue() const;
		/* returns: money in decimal form (e.g., 2.98) */

		Money percent(int percentFigure) const;
		/* returns: a percentage of the money amount specified by "percentFigure," in the form of a Money object. */

		friend istream& operator >>(istream& ins, Money& amount);
		/* asks for a set of characters in sequence. */
		/* an example sequence: -$2.08 */
		/* the negative sign ("-") is optional. */
		/* every prompt asks for the subsequent character in the sequence - except for the prompt for a dollar amount. in that case, multiple digits could be submitted . */

		friend ostream& operator <<(ostream& outs, const Money& amount);
		/* outputs money in the following form: */
		/* "- $2.08" */

	private:
		long allCents;
};

#endif