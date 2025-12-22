#pragma once

#include <sys/time.h>

#include <algorithm>
#include <climits>
#include <cmath>
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
	void isSorted();
	static int getWorstCase(int size);
	int totalComp;

	/* Functor for comparisons */
	struct Comp {
		int &count;
		Comp(int &counter) : count(counter) {}
		bool operator()(const int &a, const int &b);
	};

  private:
	PmergeMe();
	void _fillContainers(char **argv);
	double _getTime() const;

	/* Vector */
	double _vecTime;
	std::vector<int> _vec;
	void _fordJohnson(std::vector<int> &vec);

	/* Deque */
	double _deqTime;
	std::deque<int> _deq;
	void _fordJohnson(std::deque<int> &deq);

	template <typename T> void _genJacobst(size_t pendSize, T &ctr) {
		ctr.push_back(0);
		ctr.push_back(1);

		size_t prev = 1;
		size_t prev_prev = 0;

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
