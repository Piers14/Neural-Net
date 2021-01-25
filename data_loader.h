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
	data_loader(std::string _file_path, int _batch_size = 16, double _valid_pct = 0.2);

	std::pair<std::vector<std::string>, matrix<double>> read_csv();

	void update_batch_inds();

	matrix<double> get_batch_x();

	matrix<double> get_batch_y();

	void show_batch();
	


	void set_batch_size(int _batch_size);

	int get_batch_size();
	int get_train_size();



	// Testers
	void get_batch_inds()
	{
		for (int j = 0; j < batch_size; j++)
		{
			std::cout << batch_inds[current_batch_ctr][j] << " ";
		}
		std::cout << std::endl;
	}

	void get_train_x()
	{
		std::cout << train_x << std::endl;
	}
};

