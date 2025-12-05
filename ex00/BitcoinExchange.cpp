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

/* Public Methods */

void BitcoinExchange::mapDatabase() {
	std::string filename("misc/data.csv");
	std::ifstream dbFile(filename.c_str());
	std::string line;

	_checkAndSkipHeader(filename, dbFile, DB_HEADER);

	while (std::getline(dbFile, line)) {
		std::string date = line.substr(0, 10);
		float value = static_cast<float>(strtod(line.c_str() + 11, NULL));
		_database.insert(std::pair<std::string, float>(date, value));
	}

	if (dbFile.bad()) {
		std::perror(("Error while reading file " + filename).c_str());
		throw std::exception(); // TODO créer what() avec runtime_error
	}
}

void BitcoinExchange::processInput(std::string file) {
	std::ifstream inputFile(file.c_str());
	std::string line;
	float value = 0;

	_checkAndSkipHeader(file, inputFile, INPUT_HEADER);

	while(std::getline(inputFile, line)) {
		if (line.empty())
			continue;

		size_t pipePos = line.find('|');
		if (pipePos != 11) {
			std::cout << ERROR << "bad input => " << line << '\n';
			continue;
		}

		std::string date = line.substr(0, pipePos - 1);
		std::string valueStr = line.substr(pipePos + 2);

		if (_validateDate(date) == false || _validateValue(valueStr, value) == false)
			continue;

		_printValue(date, value);
	}
}

/* Private Methods */

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

bool BitcoinExchange::_validateDate(std::string& date) {
	if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
		std::cout << ERROR << "bad input => " << date << '\n';
		return false;
	}

	char *endptr = NULL;

	long year = std::strtol(date.c_str(), &endptr, 10);
	if (*endptr != '-' || year < 1) {
		std::cout << ERROR << "bad year => " << date;
		return false;
	}

	long month = std::strtol(date.c_str() + 5, &endptr, 10);
	if (*endptr != '-' || month < 1 || month > 12) {
		std::cout << ERROR << "bad month => " << date << '\n';
		return false;
	}

	long day = std::strtol(date.c_str() + 8, NULL, 10);
	if (day < 1 || day > 31) {
		std::cout << ERROR << "bad day => " << date << '\n';
		return false;
	}
	else if (_checkDayWithinMonth(day, month, year) == false)
		return false;
	return true;
}

bool BitcoinExchange::_validateValue(std::string& valueStr, float& value) {
	char *endptr;
	value = static_cast<float>(std::strtod(valueStr.c_str(), &endptr));

	while (*endptr != 0 && std::isspace(*endptr))
			endptr++;
	if (*endptr != 0) {
		std::cout << ERROR << "bad input => " << valueStr << '\n';
		return false;
	}

	if (value < 0) {
		std::cout << ERROR << "not a positive number.\n";
		return false;
	}
	else if (value > 1000) {
		std::cout << ERROR << "too large a number.\n";
		return false;
	}
	return true;
}

bool BitcoinExchange::_checkDayWithinMonth(long day, long month, long year) {
	static const short daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	short month_idx = static_cast<short>(month - 1);

	if (month_idx != 1 && day > daysPerMonth[month_idx]) {
		std::cout << ERROR << "day (" << day << ") out of range for month " << month << '\n';
		return false;
	}
	else if (month_idx == 1) {
		bool isLeapYear = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
		if (isLeapYear == true && day > 29) {
			std::cout << ERROR << "day (" << day << ") out of range for month " << month << '\n';
			return false;
		}
		else if (isLeapYear == false && day > 28) {
			std::cout << ERROR << "day (" << day << ") out of range for month " << month << '\n';
			return false;
		}
	}
	return true;
}

void BitcoinExchange::_printValue(std::string& date, float& value) {
	std::cout << date << " => " << value;

	std::map<std::string, float>::iterator it = _database.lower_bound(date);
}
