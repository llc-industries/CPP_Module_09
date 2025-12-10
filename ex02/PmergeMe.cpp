#include "PmergeMe.hpp"

/* Canonical orthodox */

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(char **argv) { _fillContainers(argv); }

PmergeMe::PmergeMe(const PmergeMe &other) { (void)other; }

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	(void)other;
	return *this;
}

/* Methods */

void PmergeMe::printValues(std::string prefix) {
	std::cout << prefix + ": ";
	for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); ++it)
		std::cout << *it << ' ';
	std::cout << '\n';
}

void PmergeMe::runSort() {}

void PmergeMe::printBenchmark() {
	std::cout << "Time to process a range of " << _vec.size()
			  << " with std::vector : ";

	std::cout << "Time to process a range of " << _deq.size()
			  << " with std::deque : ";
}

void PmergeMe::_fillContainers(char **argv) {
	for (size_t i = 0; argv[i]; i++) {
		long long value = strtol(argv[i], NULL, 10);
		_vec.push_back(static_cast<int>(value));
		_deq.push_back(static_cast<int>(value));
	}
}
