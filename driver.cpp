#include <iostream>
#include "activation_function.h"
#include "neural_net.h"
#include "loss_function.h"
#include "data_loader.h"

int main(int argc, char* argv[])
{
	// Data loader
	data_loader test_load("test.csv", 3, 0.0);
	std::cout << "Example batch: " << std::endl;
	test_load.show_batch();
	std::cout << std::endl << std::endl;



	// EXAMPLE
	
	// Leaky ReLu activation function
	relu test_relu(0.1);
	// Quadratic loss function
	quadratic_loss test_quad;
	// Structure: 3 input, 1 output
	std::vector<int> test_structure = { 3, 20,  1 };
	// Define and initialise the neural network
	neural_net test_nn(test_structure, test_relu, test_quad, 0.02);
	test_nn.init(test_load, 100);

	// Gets a batch
	/*
	std::pair<matrix<double>, matrix<double>> batch_test = test_load.get_batch();
	std::cout << "Output from batch: " << std::endl;
	std::cout << test_nn.feed_batch(batch_test.first) << std::endl;
	test_nn.back_prop(batch_test.second);
	*/

	test_nn.train(50);

	std::cout << "Predictions: " << std::endl;
	std::cout << test_nn.feed_forward(test_load.get_train_x().sub_rows({3}));
	std::cout << "Actual: " << std::endl;
	std::cout << test_load.get_train_y().sub_rows({ 3 }) << std::endl;
	std::cout << test_load.get_train_x().sub_rows({ 3 });

	/*
	// Example data
	std::vector<double> test_input1 = { 1.0, 1.0, 0.0 };
	std::vector<double> test_input2 = { 0.5, 0.4, 0.0 };
	std::vector<double> test_input3 = { 0.1, 0.0, 0.9 };
	std::vector<double> test_input4 = { 1.0, 0.1, 1.0 };
	std::vector<std::vector<double>> train_x = { test_input1, test_input2, test_input3, test_input4};

	matrix<double> test_output1(1, 1, 0.66);
	matrix<double> test_output2(1, 1, 0.30);
	matrix<double> test_output3(1, 1, 0.33);
	matrix<double> test_output4(1, 1, 0.7);
	std::vector<matrix<double>> train_y = { test_output1, test_output2, test_output3, test_output4};
	

	
	// Train network
	test_nn.train(train_x, train_y, 100);
	
	// Outputs predicted values
	std::cout << test_nn.feed_forward(test_input1) << test_nn.feed_forward(test_input2) << 
		test_nn.feed_forward(test_input3) << test_nn.feed_forward(test_input4);
	*/
	return 0;
}