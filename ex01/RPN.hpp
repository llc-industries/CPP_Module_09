#pragma once

#include <iostream>
#include <stack>
#include <string>

class RPN {

  public:
	/* Canonical orthodox */
	RPN();
	RPN(std::string input);
	RPN(const RPN &other);
	~RPN();
	RPN &operator=(const RPN &other);
	int getResult(std::string input);

  private:
	void _performOperation(std::stack<int> &stack, char op);
};
