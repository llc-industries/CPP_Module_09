#include "PmergeMe.hpp"

/* Canonical orthodox */

PmergeMe::PmergeMe() : _vecTime(0), _deqTime(0) {}

PmergeMe::PmergeMe(char **argv) : _vecTime(0), _deqTime(0) {
	_fillContainers(argv);
}

PmergeMe::PmergeMe(const PmergeMe &other) {
	_vecTime = other._vecTime;
	_deqTime = other._deqTime;
}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	_vecTime = other._vecTime;
	_deqTime = other._deqTime;
	_vec = other._vec;
	_deq = other._deq;
	return *this;
}

/* Methods */

void PmergeMe::printValues(std::string prefix) {
	int i = 0;
	std::cout << prefix + ": ";

	for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); ++it) {
		if (i > 9) {
			std::cout << "[...]\n";
			return;
		}
		std::cout << *it << ' ';
		i++;
	}
	std::cout << '\n';
}

void PmergeMe::runBenchmarks() {
	double start = _getTime();
	_sortVec();
	_vecTime = _getTime() - start;
}

void PmergeMe::printBenchmark() const {
	std::cout << "Time to process a range of " << _vec.size()
			  << " with std::vector : " << _vecTime << "us\n";

	std::cout << "Time to process a range of " << _deq.size()
			  << " with std::deque : " << _deqTime << "us\n";
}

void PmergeMe::_fillContainers(char **argv) {
	for (size_t i = 0; argv[i]; i++) {
		long value = strtol(argv[i], NULL, 10);
		_vec.push_back(static_cast<int>(value));
		_deq.push_back(static_cast<int>(value));
	}
}

double PmergeMe::_getTime() const {
	struct timeval now;
	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000000.0 + now.tv_usec);
}

void PmergeMe::_sortVec() { _fordJohnson(_vec); }

void PmergeMe::_fordJohnson(std::vector<int> &vec) {
	// Base case for recursion
	if (vec.size() < 2)
		return;

	// Handle straggler (if size is odd)
	int straggler = -1;
	if (vec.size() % 2 != 0) {
		straggler = vec.back();
		vec.pop_back();
	}

	std::vector<int> winners;
	std::vector<std::pair<int, int> > pairs;

	// Separate winners / Keep track of win/loose relation within recursion in
	// vector::pairs
	for (size_t i = 0; i < vec.size(); i += 2) {
		int a = vec[i];
		int b = vec[i + 1];

		if (a < b)
			std::swap(a, b);

		winners.push_back(a);
		pairs.push_back(std::make_pair(a, b));
	}

	_fordJohnson(winners); // Recursion -> get all winners in vec (size / 2)

	std::vector<int> pend;

	for (size_t i = 0; i < winners.size(); i++) { // Add loser to pend
		for (size_t j = 0; j < pairs.size(); j++) {
			if (pairs[j].first == winners[i]) { // Loser found
				pend.push_back(pairs[j].second);
				pairs.erase(pairs.begin() + j); // Loser now in pend, delete
				break;
			}
		}
	}

	winners.insert(winners.begin(), pend[0]); // Pend is smaller than winner

	vec = winners;
}
