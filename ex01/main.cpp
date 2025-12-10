#include "RPN.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error\n";
		return 1;
	}

	RPN rpn(argv[1]);

	return 0;
}
