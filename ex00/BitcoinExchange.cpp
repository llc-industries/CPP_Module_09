#include "BitcoinExchange.hpp"

/* Canonical orthodox */

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) { *this = other; }

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator= (const BitcoinExchange& other) {
	if (this == &other) return *this;
	_database = other._database;
	return *this;
}

/* Methods */

void BitcoinExchange::_checkAndSkipHeader(std::string filename, std::ifstream& filestream, std::string header) {
	std::string line;

	if (filestream.is_open() == false) {
		std::perror(("Error while opening file " + filename).c_str());
		throw std::exception();
	}

	std::getline(filestream, line);
	if (line != header) {
		std::cout << ERROR << filename << ": Invalid header";
		throw std::exception();
	}
}

void BitcoinExchange::mapDatabase() {
	std::string filename("misc/data.csv");
	std::ifstream dbFile(filename.c_str());
	std::string line;

	_checkAndSkipHeader(filename, dbFile, DB_HEADER);

	while (std::getline(dbFile, line)) {
		std::string date = line.substr(0, 10);
		float value = strtof(line.c_str() + 11, NULL);
		_database.insert(std::pair<std::string, float>(date, value));
	}

	if (dbFile.bad()) {
		std::perror(("Error while reading file " + filename).c_str());
		throw std::exception();
	}
}

void BitcoinExchange::processInput(std::string file) {
	std::ifstream inputFile(file.c_str());
	std::string line;

	_checkAndSkipHeader(file, inputFile, INPUT_HEADER);

	while(std::getline(inputFile, line)) {
		if (line.empty())
			continue;

		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos) {
			std::cout << ERROR << "bad input => " << line << '\n';
			continue;
		}

		std::string date = line.substr(0, pipePos - 1);
		std::string valueStr = line.substr(pipePos + 1);
		if (_validateDate(date) == false || _validateValue(valueStr) == false)
			continue;


	}
}

bool BitcoinExchange::_validateDate(std::string& date) {
	if (date.length() != 10 || date[4] != '-' || date[7] != '-'){
		std::cout << ERROR << "bad input => " << date << '\n';
		return false;
	}

	char *endptr = NULL;

	long year = std::strtol(date.c_str(), &endptr, 10);
	if (*endptr != '-' || year < 0) {
		std::cout << ERROR << "bad year => " << date;
		return false;
	}

	long month = std::strtol(date.c_str() + 5, &endptr, 10);
	if (*endptr != '-' || month < 0 || month > 12) {
		std::cout << ERROR << "bad month => " << date << '\n';
		return false;
	}

	long day = std::strtol(date.c_str() + 8, &endptr, 10);
	std::cout << day << '\n';
	return true;
}

bool BitcoinExchange::_validateValue(std::string& value) {
	(void) value;
	return true;
}

