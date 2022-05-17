#include <iostream>
#include <string>
#include <assert.h>

using std::cout;
using std::cin;
using std::getline;

using std::string;
using std::to_string;

using std::invalid_argument;

class TimeFormatMistake {
    public:
        TimeFormatMistake(string _input, string _message): input(_input), message(_message) {};
		
		string getInput() const {return input;};
        string getMessage() const {return message;};

    private:
        string message;
		string input;
};

string prompt() {
    string input;

    cout << "enter time in 24-hour notation: ";
    getline(cin, input);

    return input;
}

string convert(string input) {
    string hour;
    string minutes;

    bool colon = false;

    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == ':') {
            colon = true;
            continue;
        }

        if (!colon)
            hour.append(1, input[i]);
        else
            minutes.append(1, input[i]);
    }

    /* cout << "hour: " << hour << '\n'; */
    /* cout << "minutes: " << minutes << '\n'; */

	int hournum;

	try {
		hournum = stoi(hour);
	}
	catch(invalid_argument) {
		throw TimeFormatMistake(input, "hours are not a valid number");
	}

    if (hournum > 23)
        throw TimeFormatMistake(input, "hours are too big of a value.");

    string suffix = "AM";

    if (hournum > 12) {
        hournum -= 12;
        suffix = "PM";
    }
    
    if (hournum == 12)
        suffix = "PM";

	int minutesnum;
	
	try {
		minutesnum = stoi(minutes);
	}
	catch(invalid_argument) {
		throw TimeFormatMistake(input, "minutes are not a valid number");
	}

    if (minutesnum > 59)
        throw TimeFormatMistake(input, "minutes are too big of a value.");

    string conversion;

    conversion.append(to_string(hournum));
    conversion.append(1, ':');

    if (minutesnum < 10)
        conversion.append(1, '0');

    conversion.append(to_string(minutesnum));

    conversion.append(1, ' ');
    conversion.append(suffix);

    return conversion;
}

void interface() {
    while (true) {
        try {
            string input = prompt();

            string conversion = convert(input);
			cout << "that is the same as: " << conversion << '\n';

            string again;
            cout << "again? (y/n)\n";
            getline(cin, again);

            if (again[0] == 'n')
                break;

			cout << '\n';
        }

        catch(TimeFormatMistake e) {
            cout << "\nthere is no such time as " << e.getInput() << '\n';
            cout << "error message: " << e.getMessage() << "\n\n";
			cout << "try again...\n\n";
        }
    }
}

int main() {
    assert("0:00 AM" == convert("0:00"));
    assert("5:00 AM" == convert("5:00"));
    assert("12:00 PM" == convert("12:00"));
    assert("3:00 PM" == convert("15:00"));
    assert("11:59 PM" == convert("23:59"));

	interface();
	
    return 0;
}
