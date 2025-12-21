#pragma once

#include <sys/time.h>

#include <algorithm>
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
	void isVecSorted();
	void isDeqSorted();

  private:
	PmergeMe();
	void _fillContainers(char **argv);
	double _getTime() const;
	void _fordJohnson(std::vector<int> &vec);
	void _fordJohnson(std::deque<int> &deq);
	double _vecTime;
	double _deqTime;
	std::deque<int> _deq;
	std::vector<int> _vec;

	template <typename T> void _genJacobst(size_t pendSize, T &ctr) {
		ctr.push_back(1);
		ctr.push_back(3);

		size_t prev = 3;
		size_t prev_prev = 1;

		while (42) {
			size_t next = prev + 2 * prev_prev;
			ctr.push_back(next);
			if (next > pendSize)
				break;
			prev_prev = prev;
			prev = next;
		}
	}
};
