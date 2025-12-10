#include "RPN.hpp"

/* Canonical orthodox */

RPN::RPN() {}

RPN::RPN(std::string input) {
	try {
		std::cout << getResult(input) << '\n';
	} catch (const std::exception &e) {
		std::cerr << e.what();
	}
}

RPN::RPN(const RPN &other) { (void)other; }

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &other) {
	(void)other;
	return *this;
}

/* Methods */

int RPN::getResult(std::string input) {
	std::stack<int> stack;

	for (size_t i = 0; input[i]; i++) {
		if (std::isspace(input[i]))
			continue;
		if (std::isdigit(input[i])) {
			stack.push(input[i] - 48);
			continue;
		}
		if (stack.size() < 2)
			throw std::runtime_error("Error\n");
		_performOperation(stack, input[i]);
	}

	if (stack.size() != 1)
		throw std::runtime_error("Error\n");

	return stack.top();
}

void RPN::_performOperation(std::stack<int> &stack, char op) {
	int right = stack.top();
	stack.pop();
	int left = stack.top();
	stack.pop();
	int result = 0;

	switch (op) {
	case '+':
		result = left + right;
		break;
	case '-':
		result = left - right;
		break;
	case '*':
		result = left * right;
		break;
	case '/':
		if (right == 0)
			throw std::runtime_error("Error\n");
		result = left / right;
		break;

	default:
		throw std::runtime_error("Error\n");
	}

	stack.push(result);
}
