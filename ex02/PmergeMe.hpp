#pragma once

#include <deque>
#include <iostream>
#include <string>
#include <vector>

class PmergeMe {

  public:
	/* Canonical orthodox */
	PmergeMe();
	PmergeMe(char **argv);
	PmergeMe(const PmergeMe &other);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &other);

	/* Methods */
	void printValues();

  private:
	void _parseValuesFillContainers(char **argv);
	std::deque<int> _deq;
	std::vector<int> _vec;
};
