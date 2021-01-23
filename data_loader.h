#pragma once
#include "matrix.h"
#include "string"
class data_loader
{
private:
	int batch_size;
	matrix<double> data;
	std::string file_path;
	double valid_pct;

public:
	data_loader(std::string _file_path, int _batch_size = 16, double valid_pct = 0.2);
	data_loader(matrix<double> _data, int _batch_size = 16, double valid_pct = 0.2);
};

