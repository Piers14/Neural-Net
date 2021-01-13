#pragma once
#include <algorithm>
#include "matrix.h"
class activation_function
{
public:
	virtual double compute(double x) = 0;
	virtual double compute_derivative(double x) = 0;

	virtual matrix<double> compute(matrix<double> x) = 0;
	virtual matrix<double> compute_derivative(matrix<double> x) = 0;
};

class relu : public activation_function
{
public:
	relu();

	double compute(double x) {
		return std::max(x, 0.0);
	}

	double compute_derivative(double x) {
		if (x > 0) {
			return 1.0;
		}
		else {
			return 0.0;
		}
	}

	matrix<double> compute(matrix<double> x) {
		matrix<double> output_matrix(x);
		for (unsigned i = 0; i < output_matrix.get_rows(); i++)
		{
			for (unsigned j = 0; j < output_matrix.get_cols(); j++)
			{
				output_matrix(i, j) = compute(x(i, j));
			}
		}
		return output_matrix;
	}

	matrix<double> compute_derivative(matrix<double> x) {
		matrix<double> output_matrix(x);
		for (unsigned i = 0; i < output_matrix.get_rows(); i++)
		{
			for (unsigned j = 0; j < output_matrix.get_cols(); j++)
			{
				output_matrix(i, j) = compute_derivative(x(i, j));
			}
		}
		return output_matrix;
	}
};

