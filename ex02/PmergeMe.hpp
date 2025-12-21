#pragma once

#include <sys/time.h>

#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

class PmergeMe {
  public:
	/* Canonical orthodox */
	PmergeMe(char **argv);
	PmergeMe(const PmergeMe &other);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &other);

	/* Methods */
	void printValues(std::string prefix);
	void printBenchmark() const;
	void runBenchmarks();

  private:
	PmergeMe();
	void _fillContainers(char **argv);
	double _getTime() const;
	void _fordJohnson(std::vector<int> &vec);
	std::vector<size_t> genJacobst(size_t pendSize);
	double _vecTime;
	double _deqTime;
	std::deque<int> _deq;
	std::vector<int> _vec;
};
