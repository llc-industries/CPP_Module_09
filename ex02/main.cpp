#include "PmergeMe.hpp"

/*
./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
 */

bool parseValues(char **argv) {
	for (size_t i = 0; argv[i]; i++) {
		char *endptr = NULL;
		long value = std::strtol(argv[i], &endptr, 10);
		if (*endptr != '\0' || value < 0 || value > INT_MAX)
			return false;
	}
	return true;
}

int main(int argc, char **argv) {
	++argv;
	if (argc < 2 || parseValues(argv) == false) {
		std::cerr << "Error\n";
		return 1;
	}

	PmergeMe FJMI(argv);

	FJMI.printValues("Before");
	FJMI.runBenchmarks();
	FJMI.printValues("After");
	FJMI.printBenchmark();

	FJMI.isSorted();

	return 0;
}
