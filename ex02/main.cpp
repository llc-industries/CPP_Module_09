#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Error\n";
		return 1;
	}

	try {
		PmergeMe pmm(argv);
		pmm.printValues();
	} catch (const std::exception &e) {
		std::cerr << e.what();
		return 1;
	}

	return 0;
}
