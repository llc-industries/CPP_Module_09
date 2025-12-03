#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	if (argc < 2) { std::cout << ERROR <<  "You need to provide a file\n"; return 1; }
	else if (argc > 2) { std::cout << ERROR << "Too many arguments\n"; return 1; }

	BitcoinExchange be;

	try { be.mapDatabase(); }
	catch (const std::exception& e) { return 1; }

	try { be.processInput(argv[1]); }
	catch (const std::exception& e) { return 1; }

	return 0;
}
