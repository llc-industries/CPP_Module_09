#pragma once

#include <cstdlib>
#include <ctime>
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
	void runSort();
	void printBenchmark();

  private:
	PmergeMe();
	void _fillContainers(char **argv);
	std::deque<int> _deq;
	std::vector<int> _vec;
};
