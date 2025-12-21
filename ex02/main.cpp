#include "PmergeMe.hpp"

/*
./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
 */

bool parseValues(char **argv) {
	for (size_t i = 0; argv[i]; i++) {
		char *endptr = NULL;
		long long value = std::strtol(argv[i], &endptr, 10);

		if (*endptr != '\0' || value < 0 || value > __INT32_MAX__)
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

	std::cout << '\n';
	FJMI.printBenchmark();
	FJMI.isVecSorted();
	FJMI.isDeqSorted();

	return 0;
}
