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

void neural_net::init(int seed)
{
	// Instatiates matrices
	num_layers = structure.size();
	assert(num_layers > 1);
	std::vector<matrix<double>> _weights(num_layers - 1);
	std::vector<matrix<double>> _bias(num_layers - 1);
	std::vector<matrix<double>> _pre_activations(num_layers - 1);
	std::vector<matrix<double>> _activations(num_layers - 1);
	std::vector<matrix<double>> _errors(num_layers - 1);


	for (int i = 0; i < num_layers - 1; i++)
	{
		_weights[i].resize(structure[i + 1], structure[i]);
		_bias[i].resize(structure[i + 1], 1);
		_pre_activations[i].resize(structure[i + 1], 1);
		_activations[i].resize(structure[i + 1], 1);
		_errors[i].resize(structure[i + 1], 1);

		
		NormalGenerator random_normal(seed + i, 0, 1.0 / (structure[i]));
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
	errors = _errors;
}

matrix<double> neural_net::feed_forward(std::vector<double> input)
{
	assert(input.size() == structure[0]);
	matrix<double> input_mat(input.size(), 1, input);
	current_input = input_mat;
	pre_activations[0] = weights[0] * input_mat + bias[0];
	activations[0] = a_fn.compute(pre_activations[0]);
	for (int i = 1; i < num_layers - 1; i++)
	{
		pre_activations[i] = weights[i] * pre_activations[i - 1] + bias[i];
		activations[i] = a_fn.compute(pre_activations[i]);
	}
	
	return activations[num_layers - 2];
}

matrix<double> neural_net::feed_batch(matrix<double> input)
{
	// Data should be pre-transposed before passed to this function
	int batch_size = input.get_cols();

	return matrix<double>();
}

std::vector<matrix<double>> neural_net::compute_deltas(matrix<double> true_value)
{
	std::vector<matrix<double>> deltas = errors;
	deltas[num_layers - 2] = loss_fn.compute_derivative(activations[num_layers - 2], true_value) % 
		a_fn.compute_derivative(pre_activations[num_layers - 2]);
	if (num_layers == 2)
	{
		errors = deltas;
		return deltas;
	}
	else
	{
		for (int i = num_layers - 3; i >= 0; i--)
		{
			deltas[i] = (weights[i + 1].transpose() * deltas[i + 1]) % a_fn.compute_derivative(pre_activations[i]);
		}
		errors = deltas;
		return deltas;
	}
	
}

void neural_net::update_weights()
{
	bias[0] -= errors[0] * learn_rate;
	weights[0] -=  errors[0] * (current_input * learn_rate).transpose();
	
	for (int i = 1; i < num_layers - 1; i++)
	{
		bias[i] -= errors[i] * learn_rate;
		weights[i] -= errors[i] * (activations[i - 1] * learn_rate).transpose();
	}
}

void neural_net::back_prop(matrix<double> true_value)
{
	compute_deltas(true_value);
	update_weights();
}

void neural_net::train(std::vector<std::vector<double>> x, std::vector<matrix<double>> y, int epochs)
{
	for (int i = 0; i < epochs; i++)
	{
		for (unsigned j = 0; j < x.size(); j++)
		{
			feed_forward(x[j]);
			back_prop(y[j]);
		}
		learn_rate *= 1.0;
	}
}
