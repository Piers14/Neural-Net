#include "neural_net.h"

neural_net::neural_net(std::vector<int> other_structure, activation_function& other_fn, double other_learn_rate)
	: structure(other_structure), a_fn(other_fn), learn_rate(other_learn_rate)
{
}

neural_net::neural_net(neural_net& other_nn)
	: structure(other_nn.structure), a_fn(other_nn.a_fn), learn_rate(other_nn.learn_rate)
{
}

void neural_net::init()
{
	// Instatiates matrices
	int num_layers = structure.size();
	std::vector<matrix<double>> _weights(num_layers - 1);
	std::vector<matrix<double>> _bias(num_layers - 1);
	std::vector<matrix<double>> _inputs(num_layers - 1);
	for (int i = 0; i < num_layers - 1; i++)
	{
		_weights[i].resize(structure[i + 1], structure[i]);
		_bias[i].resize(structure[i + 1], 1);
		_inputs[i].resize(structure[i + 1], 1);
		
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
	inputs = _inputs;
}
