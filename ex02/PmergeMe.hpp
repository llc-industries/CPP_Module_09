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
	int totalComp;

	/* Functor for comparisons */
	struct Comp {
		Comp(int &counter) : count(counter) {}
		int &count;
		bool operator()(const int &a, const int &b) {
			count++;
			return a < b;
		}
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
