#pragma once
#include <vector>
#include <cmath>
#include <cassert>
#include "matrix.h"
#include "activation_function.h"
#include "NormalGenerator.hpp"
#include "loss_function.h"

class neural_net
{
private:
	std::vector<int> structure;
	activation_function& a_fn;
	loss_function& loss_fn;
	double learn_rate;

	int num_layers;
	std::vector<matrix<double>> weights;
	std::vector<matrix<double>> bias;
	std::vector<matrix<double>> errors;
	std::vector<matrix<double>> activations;
	std::vector<matrix<double>> pre_activations;

	

public:
	neural_net(std::vector<int> structure, activation_function& other_fn, loss_function& other_loss, double other_learn_rate);
	neural_net(neural_net& other_nn);

	void init();

	matrix<double> feed_forward(std::vector<double> input);
	std::vector<matrix<double>> compute_deltas(matrix<double> true_value);
	void update_weights();
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

