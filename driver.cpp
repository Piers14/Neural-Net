#include <iostream>
#include "activation_function.h"
#include "neural_net.h"
#include "loss_function.h"

int main(int argc, char* argv[])
{
	relu test_relu;
	quadratic_loss test_quad;
	
	std::vector<int> test_structure = { 3, 1 };
	neural_net test_nn(test_structure, test_relu, test_quad, 0.04);
	test_nn.init();
	test_nn.test_weights();

	std::vector<double> test_input1 = { 1.0, 2.0, 3.0 };
	//std::vector<double> test_input2 = { 1.0, 2.0, 2.0 };
	//std::vector<double> test_input3 = { 1.4, 1.7, 2.0 };
	//std::vector<double> test_input4 = { 1.0, 1.0, 1.0 };
	std::vector<std::vector<double>> train_x = { test_input1};


	matrix<double> test_output1(1, 1, 2.0);
	//matrix<double> test_output2(1, 1, 2.0);
	//matrix<double> test_output3(1, 1, 2.0);
	//matrix<double> test_output4(1, 1, 2.0);
	std::vector<matrix<double>> train_y = { test_output1};

	//test_nn.train(train_x, train_y, 10);
	for (int i = 0; i < 20; i++)
	{
		std::cout << test_nn.feed_forward(test_input1) << std::endl;
		test_nn.compute_deltas(test_output1);
		test_nn.update_weights();
	}
	
	std::cout << test_nn.feed_forward(test_input1);


	
	


	return 0;
}