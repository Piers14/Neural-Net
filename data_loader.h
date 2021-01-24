#pragma once
#include "matrix.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <algorithm> // std::shuffle
#include <cmath> // floor
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

	std::string file_path;


public:
	data_loader(std::string _file_path, int _batch_size = 16, double _valid_pct = 0.2);

	std::pair<std::vector<std::string>, matrix<double>> read_csv();

	std::vector<int> shuffle_order(const int seed);



	// Testers
};

