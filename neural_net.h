#pragma once
#include <vector>
#include <cmath>
#include "matrix.h"
#include "activation_function.h"
#include "NormalGenerator.hpp"
class neural_net
{
private:
	std::vector<int> structure;
	activation_function& a_fn;
	double learn_rate;

	std::vector<matrix<double>> weights;
	std::vector<matrix<double>> bias;
	std::vector<matrix<double>> errors;
	std::vector<matrix<double>> activations;
	std::vector<matrix<double>> inputs;

	

public:
	neural_net(std::vector<int> structure, activation_function& other_fn, double other_learn_rate);
	neural_net(neural_net& other_nn);

	void init();

	void feed_forward(std::vector<double> input);
	void back_prop(std::vector<double> output);

	void train(matrix<double> x, std::vector<double> y);

	// Testers:
	double test_act(double x) { return a_fn.compute(x); }
	void test_weights() {
		for (unsigned i = 0; i < weights.size(); i++) {
			std::cout << weights[i] << std::endl;
		}
	}



};

