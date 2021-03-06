#include "neural_net.h"

neural_net::neural_net(std::vector<int> other_structure, activation_function& other_fn, loss_function& other_loss, double other_learn_rate)
	: structure(other_structure), a_fn(other_fn), learn_rate(other_learn_rate), loss_fn(other_loss)
{
	num_layers = 0;
	data = NULL;
}

neural_net::neural_net(neural_net& other_nn)
	: structure(other_nn.structure), a_fn(other_nn.a_fn), learn_rate(other_nn.learn_rate), num_layers(other_nn.num_layers), loss_fn(other_nn.loss_fn), 
	data(other_nn.data)
{
}

void neural_net::init(data_loader& _data, int seed)
{
	data = &_data;
	// Instantiates matrices
	num_layers = structure.size();
	assert(num_layers > 1);
	std::vector<matrix<double>> _weights(num_layers - 1);
	std::vector<matrix<double>> _bias(num_layers - 1);
	std::vector<matrix<double>> _pre_activations(num_layers - 1);
	std::vector<matrix<double>> _activations(num_layers - 1);
	std::vector<matrix<double>> _errors(num_layers - 1);

	// Same but for mini-batches
	std::vector<matrix<double>> _batch_bias(num_layers - 1);
	std::vector<matrix<double>> _batch_pre_activations(num_layers - 1);
	std::vector<matrix<double>> _batch_activations(num_layers - 1);
	std::vector<matrix<double>> _batch_errors(num_layers - 1);

	// Same but for final mini-batch
	std::vector<matrix<double>> _final_batch_pre_activations(num_layers - 1);
	std::vector<matrix<double>> _final_batch_activations(num_layers - 1);
	std::vector<matrix<double>> _final_batch_errors(num_layers - 1);
	

	for (int i = 0; i < num_layers - 1; i++)
	{
		_weights[i].resize(structure[i + 1], structure[i]);
		_bias[i].resize(structure[i + 1], 1);
		_pre_activations[i].resize(structure[i + 1], 1);
		_activations[i].resize(structure[i + 1], 1);
		_errors[i].resize(structure[i + 1], 1);

		_batch_bias[i].resize(structure[i + 1], data->get_batch_size());
		_batch_pre_activations[i].resize(structure[i + 1], data->get_batch_size());
		_batch_activations[i].resize(structure[i + 1], data->get_batch_size());
		_batch_errors[i].resize(structure[i + 1], data->get_batch_size());

		if (data->final_batch_size)
		{
			_final_batch_pre_activations[i].resize(structure[i + 1], data->final_batch_size);
			_final_batch_activations[i].resize(structure[i + 1], data->final_batch_size);
			_final_batch_errors[i].resize(structure[i + 1], data->final_batch_size);
		}
		

		// Initialises weights
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

	batch_bias = _batch_bias;
	batch_pre_activations = _batch_pre_activations;
	batch_activations = _batch_activations;
	batch_errors = _batch_errors;

	final_batch_pre_activations = _final_batch_pre_activations;
	final_batch_activations = _final_batch_activations;
	final_batch_errors = _final_batch_errors;
}

matrix<double> neural_net::feed_forward(matrix<double> input)
{
	assert(input.get_cols() == structure[0]);
	current_input = input.transpose();
	pre_activations[0] = weights[0] * current_input + bias[0];
	activations[0] = a_fn.compute(pre_activations[0]);
	for (int i = 1; i < num_layers - 1; i++)
	{
		pre_activations[i] = weights[i] * pre_activations[i - 1] + bias[i];
		activations[i] = a_fn.compute(pre_activations[i]);
	}
	
	return activations[num_layers - 2];
}

matrix<double> neural_net::feed_batch(matrix<double> input_batch)
{
	assert(input_batch.get_cols() == structure[0]);
	current_batch = input_batch.transpose();
	if (input_batch.get_rows() != data->get_batch_size())
	{
		// Case when smaller than ususal batch size
		std::vector<int> final_bs_inds(data->final_batch_size);
		for (int i = 0; i < final_bs_inds.size(); i++)
		{
			final_bs_inds[i] = i;
		}

		final_batch_pre_activations[0] = weights[0] * input_batch.transpose() + batch_bias[0].sub_cols(final_bs_inds);
		final_batch_activations[0] = a_fn.compute(final_batch_pre_activations[0]);

		for (int i = 1; i < num_layers - 1; i++)
		{
			final_batch_pre_activations[i] = weights[i] * final_batch_pre_activations[i - 1] + batch_bias[i].sub_cols(final_bs_inds);
			final_batch_activations[i] = a_fn.compute(final_batch_pre_activations[i]);
		}

		return final_batch_activations[num_layers - 2];
	}

	// First layer
	batch_pre_activations[0] = weights[0] * input_batch.transpose() + batch_bias[0];
	batch_activations[0] = a_fn.compute(batch_pre_activations[0]);

	
	// Other layers
	for (int i = 1; i < num_layers - 1; i++)
	{
		batch_pre_activations[i] = weights[i] * batch_pre_activations[i - 1] + batch_bias[i];
		batch_activations[i] = a_fn.compute(batch_pre_activations[i]);
	}
	
	return batch_activations[num_layers - 2];
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

std::vector<matrix<double>> neural_net::compute_batch_deltas(matrix<double> true_values)
{
	std::vector<matrix<double>> batch_deltas = batch_errors;
	batch_deltas[num_layers - 2] = (loss_fn.compute_derivative(batch_activations[num_layers - 2], true_values.transpose()) %
		a_fn.compute_derivative(batch_pre_activations[num_layers - 2]));
	if (num_layers == 2)
	{
		batch_errors = batch_deltas;
		return batch_errors;
	}
	else
	{
		for (int i = num_layers - 3; i >= 0; i--)
		{
			batch_deltas[i] = (weights[i + 1].transpose() * batch_deltas[i + 1]) % a_fn.compute_derivative(batch_pre_activations[i]);
		}
		batch_errors = batch_deltas;
		return batch_deltas;
	}
}

void neural_net::average_batch_deltas()
{
	for (int i = 0; i < num_layers - 1; i++)
	{
		//errors[i] = batch_errors[i].row_means();
	}
}

void neural_net::update_weights()
{
	/*
	bias[0] -= errors[0] * learn_rate;
	weights[0] -=  errors[0] * (current_input * learn_rate).transpose();
	
	for (int i = 1; i < num_layers - 1; i++)
	{
		bias[i] -= errors[i] * learn_rate;
		weights[i] -= errors[i] * (activations[i - 1] * learn_rate).transpose();
	}
	*/

	bias[0] -= batch_errors[0].row_means() * learn_rate;
	weights[0] -= batch_errors[0] * (current_batch * (learn_rate / batch_errors[0].get_cols())).transpose();

	for (int i = 1; i < num_layers - 1; i++)
	{
		bias[i] -= batch_errors[i].row_means() * learn_rate;
		weights[i] -= batch_errors[i] * (batch_activations[i - 1] * (learn_rate / batch_errors[i].get_cols())).transpose();
	}
}

void neural_net::back_prop(matrix<double> true_values)
{
	compute_batch_deltas(true_values);
	average_batch_deltas();
	update_weights();
}

void neural_net::train(int epochs)
{
	
	for (int i = 0; i < epochs; i++)
	{
		for (int j = 0; j < data->num_batches; j++)
		{
			std::pair<matrix<double>, matrix<double>> next_batch = data->get_batch();
			feed_batch(next_batch.first);
			back_prop(next_batch.second);
		}
		
	}
	
}
