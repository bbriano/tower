#include <fstream>
#include <iostream>

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

string readInput(string prompt = "") {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
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
