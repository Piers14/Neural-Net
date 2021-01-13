#pragma once
#include <vector>
#include "matrix.h"
class neural_net
{
private:
	std::vector<int> structure;
	std::vector<matrix<double>> weights;
	std::vector<matrix<double>> bias;
	std::vector<matrix<double>> errors;
	double learn_rate;

public:
	neural_net(std::vector<int> structure);
	neural_net(neural_net& other_nn);

	void feed_forward(std::vector<double> input);
	void back_prop(std::vector<double> output);

	void train(matrix<double> x, std::vector<double> y);



};

