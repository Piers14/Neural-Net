#pragma once
#include <vector>
#include "matrix.h"
#include "cassert"
class loss_function
{
public:
	virtual double compute(matrix<double> predicted, matrix<double> actual) = 0;
	virtual matrix<double> compute_derivative(matrix<double> predicted, matrix<double> actual) = 0;
};

class quadratic_loss : public loss_function
{
public:
	quadratic_loss(){}
	double compute(matrix<double> predicted, matrix<double> actual) {
		assert(predicted.get_rows() == actual.get_rows());
		double output = 0;
		for (unsigned i = 0; i < predicted.get_rows(); i++)
		{
			output += (actual(i, 0) - predicted(i, 0)) * (actual(i, 0) - predicted(i, 0));
		}
		output *= 0.5;
		return output;
	}
	matrix<double> compute_derivative(matrix<double> predicted, matrix<double> actual) {
		assert(predicted.get_rows() == actual.get_rows());
		assert(predicted.get_cols() == actual.get_cols());
		matrix<double> output(predicted.get_cols(), predicted.get_rows(), 0);
		output = predicted - actual;
		return output;
	}
};

