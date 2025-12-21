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

void PmergeMe::printBenchmark() const {
	std::cout << "Time to process a range of " << _vec.size()
			  << " with std::vector : " << _vecTime << "us\n";

	std::cout << "Time to process a range of " << _deq.size()
			  << " with std::deque : " << _deqTime << "us\n";
}

void PmergeMe::runBenchmarks() {
	double start = _getTime();
	_fordJohnson(_vec);
	_vecTime = _getTime() - start;
}

/* Private Methods */

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

/* Ford Johnson with std::vector */

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
				pairs.erase(pairs.begin() + j); // Loser now in pend, delt pair
				break;
			}
		}
	}

	if (pend.empty() == false)
		winners.insert(winners.begin(), pend[0]); // Pend < winner in same idx

	size_t last_inserted = 0;
	std::vector<size_t> jacob = genJacobst(pend.size());

	for (size_t i = 1; i < jacob.size(); i++) { // Binary insertion
		size_t index = jacob[i] - 1;			// Get jacob idx
		if (index >= pend.size())
			index = pend.size() - 1;

		while (index > last_inserted) { // Binay insertion using jacob
			std::vector<int>::iterator it =
				std::lower_bound(winners.begin(), winners.end(), pend[index]);
			winners.insert(it, pend[index]);
			index--;
		}
		last_inserted = jacob[i] - 1; // Update for next pair
	}

	if (straggler != -1) { // Put straggler back
		std::vector<int>::iterator pos =
			std::lower_bound(winners.begin(), winners.end(), straggler);
		winners.insert(pos, straggler);
	}

	vec = winners;
}

std::vector<size_t> PmergeMe::genJacobst(size_t pendSize) {
	std::vector<size_t> jacob;
	jacob.push_back(1);
	jacob.push_back(3);

	size_t prev = 3;
	size_t prev_prev = 1;

	while (42) {
		size_t next = prev + 2 * prev_prev;
		jacob.push_back(next);
		if (next > pendSize)
			break;
		prev_prev = prev;
		prev = next;
	}
	return jacob;
}
