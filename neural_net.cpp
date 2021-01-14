#include "neural_net.h"

neural_net::neural_net(std::vector<int> other_structure, activation_function& other_fn, loss_function& other_loss, double other_learn_rate)
	: structure(other_structure), a_fn(other_fn), learn_rate(other_learn_rate), loss_fn(other_loss)
{
	num_layers = 0;
}

neural_net::neural_net(neural_net& other_nn)
	: structure(other_nn.structure), a_fn(other_nn.a_fn), learn_rate(other_nn.learn_rate), num_layers(other_nn.num_layers), loss_fn(other_nn.loss_fn)
{
}

void neural_net::init()
{
	// Instatiates matrices
	num_layers = structure.size();
	std::vector<matrix<double>> _weights(num_layers - 1);
	std::vector<matrix<double>> _bias(num_layers - 1);
	std::vector<matrix<double>> _pre_activations(num_layers - 1);
	std::vector<matrix<double>> _activations(num_layers - 1);

	for (int i = 0; i < num_layers - 1; i++)
	{
		_weights[i].resize(structure[i + 1], structure[i]);
		_bias[i].resize(structure[i + 1], 1);
		_pre_activations[i].resize(structure[i + 1], 1);
		_activations[i].resize(structure[i + 1], 1);
		
		NormalGenerator random_normal(1, 0, 1.0 / sqrt(structure[i + 1]));
		for (unsigned j = 0; j < _weights[i].get_rows(); j++)
		{
			for (unsigned k = 0; k < _weights[i].get_cols(); k++)
			{
				_weights[i](j, k) = random_normal.rng();
			}
		}
	}
	weights = _weights;
	bias = _bias;
	pre_activations = _pre_activations;
	activations = _activations;
}

matrix<double> neural_net::feed_forward(std::vector<double> input)
{
	assert(input.size() == structure[0]);
	matrix<double> input_mat(input.size(), 1, input);
	pre_activations[0] = weights[0] * input_mat + bias[0];
	activations[0] = a_fn.compute(pre_activations[0]);
	for (int i = 1; i < num_layers - 1; i++)
	{
		pre_activations[i] = weights[i] * input_mat + bias[i];
		activations[i] = a_fn.compute(pre_activations[i]);
	}
	
	return activations[num_layers - 2];
}

std::vector<matrix<double>> neural_net::compute_deltas(matrix<double> true_value)
{
	std::vector<matrix<double>> deltas = errors;
	deltas[num_layers - 2] = loss_fn.compute_derivative(activations[num_layers - 2], true_value) % 
		a_fn.compute_derivative(pre_activations[num_layers - 2]);
	for (int i = num_layers - 3; i >= 0; i--)
	{
		deltas[i] = (weights[i + 1].transpose() * deltas[i + 1]) % a_fn.compute_derivative(pre_activations[i]);
	}
	return deltas;
}
