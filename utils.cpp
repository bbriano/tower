/************************************************************
 *
 * utils.cpp
 *
 * A collection of helper functions to avoid repetition
 *
 * Briano Goestiawan, 31482228
 *
************************************************************/

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "utils.h"
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

// Returns the content of a file specified by fileName
string readFile(string fileName) {
    ifstream file;
    file.open(fileName);

    // If file failed to open
    if (!file.is_open()) {
        cout << "ERROR: cannot open file: " << fileName << endl;
        return "";
    }

    // Append each line in file to content
    string content;
    string line;
    getline(file, content);
    while (!file.eof()) {
        getline(file, line);
        content += '\n' + line;
    }
    file.close();

    return content;
}

// Write content to file named fileName, overwrite if it exists
void writeFile(string fileName, string content) {
    ofstream file;
    file.open(fileName);

    // If file failed to open
    if (!file.is_open()) {
        cout << "ERROR: cannot open file" << fileName << endl;
        return;
    }

    file << content;
    file.close();
}

// Split string to vector of strings based on character
vector<string> stringSplit(string content, char character) {
    vector<string> lines;

    // Push to lines when content matches character
    int prev = 0;
    for (int i = 0; i < content.length(); i++) {
        if (content[i] == character) {
            lines.push_back(content.substr(prev, i - prev));
            prev = i + 1;
        }
    }

    // Check if last element if delimitered else ignore
    string end = content.substr(prev);
    if (end.length() > 0) {
        lines.push_back(end);
    }

    return lines;
}

// Join vector of string into one string used character
string stringJoin(vector<string> lines, char character) {
    string result = "";

    for (int i = 0; i < lines.size(); i++) {
        result += lines[i] + character;
    }

    return result;
}

// Print promp to screen then read and return input line
string readInput(string prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

// Print prompt to screen then read input as int. Repeat until user input an int
int readInputInt(string prompt) {
    string input;
    do {
        input = readInput("Pick one option (1-4): ");
    } while(!isInteger(input));
    return stoi(input);
}

// Pause the control flow until the user press enter
void pause() {
    readInput("Press Enter to continue ");
}

// Cross platform clear command
void clearScreen() {
    system(CLEAR);
}

// Return true if value is an integer string else return false
bool isInteger(std::string value) {
    // Empty string is not an integer
    if (value.length() <= 0) {
        return false;
    }

    // Set first index to be checked to allow negative integers
    int firstDigitIndex = 0;
    if (value[0] == '-')
        firstDigitIndex = 1;

    // Check if any characters is not a digit
    for (int i = firstDigitIndex; i < value.length(); i++)
        if (value[i] < '0' or value[i] > '9')
            return false;

    // It survived all the previous tests. It must be an integer
    return true;
}

// Returns a copy of value with all the uppercase characters replaced with its lowercase equivalent
string toLower(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 'a' - 'A';
        }
    }
    return str;
}

// Returns a string with a fixed width and align text to the left
string fixedWidth(string text, char symbol, int width) {
    string output = "";

    for (int i = 0; i < width; i++) {
        if (i < text.length()) {
            output += text[i];
        } else {
            output += symbol;
        }
    }

    return output;
}

// Returns seconds time in hour:min:sec string format
string toHourMinuteSeconds(int seconds) {
    int hour = seconds / 60 / 60;
    int min = seconds / 60 % 60;
    int sec = seconds % 60;
    stringstream output;
    output << hour << ':' << min << ':' << sec;
    return output.str();
}
