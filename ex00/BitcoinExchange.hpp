#pragma once

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#define RESET "\033[0m"
#define RED "\033[31m"
#define ERROR RED "Error" RESET ": "

#define DB_HEADER "date,exchange_rate"
#define INPUT_HEADER "date | value"

class BitcoinExchange {

  public:
	/* Canonical orthodox */
	BitcoinExchange();
	BitcoinExchange(const std::string input);
	BitcoinExchange(const BitcoinExchange &other);
	~BitcoinExchange();
	BitcoinExchange &operator=(const BitcoinExchange &other);

	/* Methods */
	void mapDatabase();
	void processInput(std::string file);

  private:
	void _checkAndSkipHeader(std::string filename, std::ifstream &filestream,
							 std::string header);
	bool _validateDate(std::string &date);
	bool _validateValue(std::string &valueStr, float &value);
	bool _checkDayWithinMonth(long day, long month, long year);
	void _printValue(std::string &date, float &value);
	std::map<std::string, float> _database;
};
