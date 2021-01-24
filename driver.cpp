#include <iostream>
#include "activation_function.h"
#include "neural_net.h"
#include "loss_function.h"
#include "data_loader.h"

int main(int argc, char* argv[])
{
	// Read in csv example
	data_loader test_loader("test.csv");
	std::pair<std::vector<std::string>, matrix<double>> test_data = test_loader.read_csv();
	std::cout << test_data.second << std::endl;

	// EXAMPLE

	// Leaky ReLu activation function
	relu test_relu(0.1);
	// Quadratic loss function
	quadratic_loss test_quad;
	// Structure: 3 input, 1 output, two hidden layers with 20 neurons in each
	std::vector<int> test_structure = { 3, 20, 20, 1 };

	// Define and initialise the neural network
	neural_net test_nn(test_structure, test_relu, test_quad, 0.1);
	test_nn.init(100);

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

	/*
	test_nn.test_weights();
	std::cout << std::endl;
	std::cout << test_nn.feed_forward(test_input1) << std::endl;
	for (int i = 0; i < 10; i++)
	{
		test_nn.back_prop(test_output1);
		test_nn.test_weights();
		std::cout << std::endl;
		std::cout << "Prediction: " << test_nn.feed_forward(test_input1) << std::endl;
	}
	*/

	
	// Train network
	//test_nn.train(train_x, train_y, 100);
	
	// Outputs predicted values
	std::cout << test_nn.feed_forward(test_input1) << test_nn.feed_forward(test_input2) << 
		test_nn.feed_forward(test_input3) << test_nn.feed_forward(test_input4);
	
	return 0;
}