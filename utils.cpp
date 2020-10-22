#include <fstream>
#include <iostream>
#include <sstream>
#include "utils.h"

using namespace std;

string readFile(string fileName) {
    ifstream file;
    file.open(fileName);

    // If file failed to open
    if (!file.is_open()) {
        cout << "ERROR: cannot open file" << fileName << endl;
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

    return content;
}

string readInput(string prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

int readInputInt(string prompt) {
    string input;
    do {
        input = readInput("Pick one option (1-4): ");
    } while(!isInteger(input));
    return stoi(input);
}

void pause() {
    readInput("Press Enter to continue ");
}

// Cross platform clear command
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
void clearScreen() {
    system(CLEAR);
}

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

string toLower(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 'a' - 'A';
        }
    }
    return str;
}

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

string toHourMinuteSeconds(int seconds) {
    int hour = seconds / 60 / 60;
    int min = seconds / 60 % 60;
    int sec = seconds % 60;
    stringstream output;
    output << hour << ':' << min << ':' << sec;
    return output.str();
}
