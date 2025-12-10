#include "PmergeMe.hpp"

/* Canonical orthodox */

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(char **argv) { _parseValuesFillContainers(argv); }

PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	(void)other;
	return *this;
}

/* Methods */

void PmergeMe::printValues() {
	std::cout << "Before: ";
	for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); ++it)
		std::cout << *it << ' ';
}

void PmergeMe::_parseValuesFillContainers(char **argv) {
	for (size_t i = 0; argv[i]; i++) {
		char *endptr = NULL;
		long long value = strtol(argv[i], &endptr, 10);

		if (*endptr != NULL || value < 0 || value > __INT32_MAX__)
			throw std::runtime_error("Error\n");

		_deq.push_back(static_cast<int>(value));
		_vec.push_back(static_cast<int>(value));
	}
}
