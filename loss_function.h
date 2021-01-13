#pragma once
#include <vector>
class loss_function
{
public:
	virtual std::vector<double> compute(std::vector<double> predicted, std::vector<double> actual) = 0;
	virtual std::vector<double> compute_derivative(std::vector<double> predicted, std::vector<double> actual) = 0;
};

class quadratic_loss : public loss_function
{
public:
	std::vector<double> compute(std::vector<double> predicted, std::vector<double> actual);
	std::vector<double> compute_derivative(std::vector<double> predicted, std::vector<double> actual);
};

