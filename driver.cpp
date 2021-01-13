#include <iostream>
#include "activation_function.h"
#include "neural_net.h"

int main(int argc, char* argv[])
{
	relu test_function;
	std::vector<int> test_structure = { 1, 1 };
	neural_net test_nn(test_structure, test_function, 1);
	test_nn.init();

	test_nn.test_weights();

	std::vector<double> test_input = { 4.0 };
	std::cout << test_nn.feed_forward(test_input);
	

	return 0;
}