#include <iostream>
#include "activation_function.h"
#include "neural_net.h"
#include "loss_function.h"

int main(int argc, char* argv[])
{
	relu test_relu;
	quadratic_loss test_quad;
	
	std::vector<int> test_structure = { 1, 1 };
	neural_net test_nn(test_structure, test_relu, test_quad, 1);
	test_nn.init();

	test_nn.test_weights();

	std::vector<double> test_input = { 4.0 };
	std::cout << test_nn.feed_forward(test_input) << std::endl;
	
	matrix<double> m1(3, 1, 4.0);
	matrix<double> m2(3, 1, 6);
	std::cout << test_quad.compute_derivative(m1, m2);


	return 0;
}