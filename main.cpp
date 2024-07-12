/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 *   Name: Reinier Garcia Ramos                                            *
 *                                                                     *
 *   Program Title: Struct Circle                                            *
 *                                                                     *
 *   Purpose:                                                          *
 *   Receives the radius as  an integer provided by the user
 *   from the console, and stores them in an array. And then based on them, it           *
 *   calculates the sum, the average and the largest element.          *
 *                                                                     *
 *   More Details:                                                     *
 *   https://github.com/reymillenium/20240621_0127_arrays_intro        *
 *                                                                     *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 **/

#include <iostream>
#include <string>
#include <cmath>
#include <climits>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <regex>

using std::cout;
using std::endl;
using std::cin;
using std::fixed;
using std::setprecision;
using std::string;
using std::to_string;
using std::stringstream;
using std::accumulate;
using std::vector;
using std::regex;
using std::regex_match;
using std::regex_search;
using std::stoi;


// STRUCTURE DEFINITIONS


struct AlternativeCircle {
    int radius {0};

    [[nodiscard]] double area() const {
        return M_PI * pow(radius, 2);
    }

    [[nodiscard]] double circumference() const {
        return 2 * M_PI * radius;
    }
};

struct Circle {
    int radius {0};
    double area {0.0};
    double circumference {0.0};
};


// UTILITY FUNCTIONS PROTOTYPES


// Determines if a given string is a valid integer, using a regular expression
bool isInteger(const string &input);

// Receives and validates an integer number from the console
int getInteger(const string &, int, int, bool = false, const string & = "Invalid input. Please try again.", const vector<int> & = {});

// Formats a given positive int by inserting a comma every 3 digits of its equivalent string, to make it more readable, by US standards
string humanizeUnsignedInteger(unsigned long long int);

// Formats a given positive double by inserting a comma every 3 digits of its equivalent string, to make it more readable, by US standards
string humanizeUnsignedDouble(long double, int = 2);


// CUSTOM MADE FUNCTIONS PROTOTYPES


// Shows the program's welcoming message
void showProgramWelcome();

// Shows the menu to the user
void showMenu();

// Calculates the area based on the radius of a given reference of a Circle structure variable, and then sets it into its respective structure's member
void calcArea(Circle &);

// Calculates the circumference based on the radius of a given reference of a Circle structure variable, and then sets it into its respective structure's member
void calcCircumference(Circle &);

// Obtains from the user the radius for a given reference of a AlternativeCircle structure variable
void getCircleInfo(AlternativeCircle &);

// Obtains from the user the radius for a given reference of a Circle structure variable
void getCircleInfo(Circle &);

// Shows all the relevant info inside a given AlternativeCircle structure variable
void displayCircleInfo(const AlternativeCircle &);

// Shows all the relevant info inside a given Circle structure variable
void displayCircleInfo(const Circle &);

// Processes the selection made by the user, based on the options of the menu
void processSelection(int);

// Main Function
int main() {
    constexpr int QUITTING_OPTION = 3; // The option number on the menu that allows to quit the program
    int menuSelectedOption = 0; // The selection made by the user from the options of the menu

    // Shows the program's welcoming message
    showProgramWelcome();

    do {
        // Shows the menu with some options to the user
        showMenu();

        // Gets the selected menu option from the user
        menuSelectedOption = getInteger("Type your selection please", 1, QUITTING_OPTION, true);

        // Processes the selection made by the user
        processSelection(menuSelectedOption);
    } while (menuSelectedOption != QUITTING_OPTION);

    return 0;
}


// UTILITY FUNCTIONS DEFINITIONS


// Determines if a given string is a valid integer, using a regular expression
bool isInteger(const string &input) {
    const regex pattern("^[+-]?[0-9]+$");
    return regex_match(input, pattern);
}

// Receives and validates an integer number from the console
int getInteger(const string &message, const int minValue, const int maxValue, const bool showRange, const string &errorMessage, const vector<int> &sentinelValues) {
    string numberAsString; // Value typed by the user, that can be an integer or not
    int number = 0; // Integer convertion (if possible) of the value typed by the user
    bool keepAsking = true; // If we must keep asking for a value to the user, until receiving an integer

    do {
        cout << message << (showRange ? (" (" + to_string(minValue) + " - " + to_string(maxValue) + ")") : "") << ": ";
        getline(cin, numberAsString);

        if (!isInteger(numberAsString)) {
            cout << "That's not an integer number. Try again." << endl;
            continue; // There is no point in keep validating any further, as it's not even an integer
        }

        number = stoi(numberAsString); // When we reach this point, that means we have a proper integer
        const bool invalidInput = number < minValue || maxValue < number; // If the input is valid, based only in minimum & maximum possible values
        // If the typed number is not among the given sentinel values (breaking values)
        const bool numberIsNotSentinel = count(sentinelValues.begin(), sentinelValues.end(), number) == 0;
        keepAsking = invalidInput && numberIsNotSentinel;
        if (keepAsking) cout << errorMessage << endl;
    } while (keepAsking);

    return number;
}

// Formats a given positive int by inserting a comma every 3 digits of its equivalent string, to make it more readable, by US standards
string humanizeUnsignedInteger(const unsigned long long int integerValue) {
    string integerAsString = to_string(integerValue);
    const int initialIndex = (integerAsString.length() - 3);
    // We insert commas into the string every three digits, fromm right to left.
    for (int j = initialIndex; j > 0; j -= 3) {
        integerAsString.insert(j, ",");
    }
    return integerAsString;
}

// Formats a given positive double by inserting a comma every 3 digits of its equivalent string, to make it more readable, by US standards
string humanizeUnsignedDouble(const long double doubleValue, const int precision) {
    const auto integerValue = static_cast<unsigned long long int>(doubleValue);
    const long double decimals = doubleValue - integerValue;
    // Extracts into a string the decimal part, rounded to two significant digits
    stringstream stream;
    // Places the decimals into the stream, rounded to two significant digits (by default)
    stream << fixed << setprecision(precision) << decimals;
    // Extracts the decimals from the stream, as a string, still rounded to two significant digits (by default)
    const string decimalsAsString = stream.str(); // It still includeds the zero & the dot. Ex: 0.34 (the dot must be removed next)
    return humanizeUnsignedInteger(integerValue) + decimalsAsString.substr(1, precision + 1);
}


// CUSTOM MADE FUNCTIONS DEFINITIONS


// Shows the program's welcoming message
void showProgramWelcome() {
    cout << endl;
    cout << "Welcome to Circle Setter Pro" << endl;
}

// Shows the menu to the user
void showMenu() {
    cout << endl;
    cout << "1. Demonstration using a Circle structure variable." << endl;
    cout << "2. Another demonstration using an AlternativeCircle structure variable." << endl;
    cout << "3. Quit the program." << endl;
    cout << endl;
}

// Calculates the area based on the radius of a given reference of a Circle structure variable, and then sets it into its respective structure's member
void calcArea(Circle &aCircle) {
    aCircle.area = M_PI * pow(aCircle.radius, 2);
}

// Calculates the circumference based on the radius of a given reference of a Circle structure variable, and then sets it into its respective structure's member
void calcCircumference(Circle &aCircle) {
    aCircle.circumference = 2 * M_PI * aCircle.radius;
}

// Obtains from the user the radius for a given reference of a AlternativeCircle structure variable
void getCircleInfo(AlternativeCircle &aCircle) {
    aCircle.radius = getInteger("Type the radius of the alternative circle please (in)", 1, INT_MAX);
}

// Obtains from the user the radius for a given reference of a Circle structure variable
void getCircleInfo(Circle &aCircle) {
    aCircle.radius = getInteger("Type the radius of the circle please (in)", 1, INT_MAX);
    calcArea(aCircle);
    calcCircumference(aCircle);
}

// Shows all the relevant info inside a given AlternativeCircle structure variable
void displayCircleInfo(const AlternativeCircle &aCircle) {
    cout << endl;
    cout << "A circle with a radius of " << aCircle.radius << " in has an area of " << humanizeUnsignedDouble(aCircle.area()) << " in²";
    cout << " and a circumference of " << humanizeUnsignedDouble(aCircle.circumference()) << " in." << endl;
}

// Shows all the relevant info inside a given Circle structure variable
void displayCircleInfo(const Circle &aCircle) {
    cout << endl;
    cout << "A circle with a radius of " << aCircle.radius << " in has an area of " << humanizeUnsignedDouble(aCircle.area) << " in²";
    cout << " and a circumference of " << humanizeUnsignedDouble(aCircle.circumference) << " in." << endl;
}

// Processes the selection made by the user, based on the options of the menu
void processSelection(const int menuSelection) {
    switch (menuSelection) {
        case 1: {
            Circle tempCircle; // Defines a Circle structure variable
            getCircleInfo(tempCircle); // Obtains the radius of the Circle structure variable from the user and makes two more calculations
            displayCircleInfo(tempCircle); // Renders the info of the Circle structure variable
            break;
        }

        case 2: {
            AlternativeCircle tempAlternativeCircle; // Defines a AlternativeCircle structure variable
            getCircleInfo(tempAlternativeCircle); // Obtains the radius of the AlternativeCircle structure variable from the user
            displayCircleInfo(tempAlternativeCircle); // Renders the info of the AlternativeCircle structure variable
            break;
        }

        default:
            break;
    }
}
