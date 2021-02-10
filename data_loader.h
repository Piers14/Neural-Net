#pragma once
#include "matrix.h"
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <algorithm> // std::random_shuffle
#include <cmath> // floor
#include <cstdlib> // std::rand

class data_loader
{
private:
	int batch_size;
	double valid_pct;

	matrix<double> train_x;
	matrix<double> train_y;
	matrix<double> val_x;
	matrix<double> val_y;
	std::vector<std::string> var_names;

	int num_vars;
	int num_obs;
	int num_train;
	int num_val;
	int num_batches;
	int final_batch_size;

	int current_batch_ctr;

	std::vector<std::vector<int>> batch_inds;

	std::string file_path;


public:
	// Constructors
	data_loader();
	data_loader(std::string _file_path, int _batch_size = 16, double _valid_pct = 0.2);
	data_loader(data_loader& other_dl);

	// Reads in the csv from the file path
	std::pair<std::vector<std::string>, matrix<double>> read_csv();

	// After a full epoch, updates the new mini-batches
	void update_batch_inds();

	// Returns the next mini-batch as a pair of the x and y values
	std::pair <matrix<double>, matrix<double>> get_batch();

	void show_batch();

	int get_batch_size() const;

	int get_train_size() const;

	matrix<double> get_train_x() const;

	matrix<double> get_train_y() const;

	friend class neural_net;
};

