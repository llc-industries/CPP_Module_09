#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

#define RESET	"\033[0m"
#define RED		"\033[31m"
#define ERROR RED "Error" RESET ": "

#define DB_HEADER "date,exchange_rate"
#define INPUT_HEADER "date | value"

class BitcoinExchange {

public:
/* Canonical orthodox */
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	~BitcoinExchange();
	BitcoinExchange& operator= (const BitcoinExchange& other);

/* Methods */
	void mapDatabase();
	void processInput(std::string file);

private:
	void _checkAndSkipHeader(std::string filename, std::ifstream& filestream, std::string header);
	/* std::string _validateDate(std::string& line);
	void _validateValue(std::string& line); */
	std::map<std::string, float> _database;

};
