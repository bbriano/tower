/************************************************************
 *
 * utils.cpp
 *
 * A collection of helper functions to avoid repetition
 *
 * Briano Goestiawan, 31482228
 *
************************************************************/

#pragma once
#include <string>

// Returns the content of a file specified by fileName
std::string readFile(std::string fileName);

// Write content to file named fileName, overwrite if it exists
void writeFile(std::string fileName, std::string content);

// Split string to vector of strings based on character
std::vector<std::string> stringSplit(std::string content, char character = '\n');

// Join vector of string into one string used character
std::string stringJoin(std::vector<std::string> lines, char character = '\n');

// Print promp to screen then read and return input line
std::string readInput(std::string prompt = "");

// Print prompt to screen then read input as int. Repeat until user input an int
int readInputInt(std::string prompt = "");

// Pause the control flow until the user press enter
void pause();

// Clear the output screen
void clearScreen();

// Return true if value is an integer string else return false
bool isInteger(std::string value);

// Returns a copy of value with all the uppercase characters replaced with its lowercase equivalent
std::string toLower(std::string value);

// Returns a string with a fixed width and align text to the left
std::string fixedWidth(std::string text, char symbol, int width);

// Returns seconds time in hour:min:sec string format
std::string toHourMinuteSeconds(int seconds);
