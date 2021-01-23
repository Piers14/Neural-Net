#pragma once
#include "matrix.h"
#include "string"
class data_loader
{
private:
	int batch_size;
	double valid_pct;

	matrix<double> train_data;
	matrix<double> val_data;
	std::string file_path;
	

public:
	data_loader(std::string _file_path, int _batch_size = 16, double valid_pct = 0.2);
	data_loader(matrix<double> _data, int _batch_size = 16, double valid_pct = 0.2);
};

