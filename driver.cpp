#include <iostream>
#include "activation_function.h"
#include "neural_net.h"

int main(int argc, char* argv[])
{
	relu test_function;
	std::vector<int> test_structure = { 4, 6, 1 };
	neural_net test_nn(test_structure, test_function, 1);
	test_nn.init();

	test_nn.test_weights();
	

	return 0;
}