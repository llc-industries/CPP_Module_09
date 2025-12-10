#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << ERROR << "could not open file.\n";
		return 1;
	} else if (argc > 2) {
		std::cout << ERROR << "Too many arguments\n";
		return 1;
	}

	BitcoinExchange be(argv[1]);

	return 0;
}
