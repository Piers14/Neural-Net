#ifndef __MATRIX_H
#define __MATRIX_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>

template <typename T> class matrix {
private:
	std::vector<std::vector<T> > mat;
	unsigned rows;
	unsigned cols;

public:
	matrix();
	matrix(unsigned _rows, unsigned _cols, const T& _initial);
	matrix(unsigned _rows, unsigned _cols, const std::vector<T> _vec);
	matrix(const matrix<T>& rhs);
	virtual ~matrix();

	void resize(unsigned new_rows, unsigned new_cols);

	// Overloading insertion operator
	template<typename T>
	friend std::ostream& operator<<(std::ostream& output, const matrix<T>& rhs);

	// Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
	matrix<T>& operator=(const matrix<T>& rhs);

	// Matrix mathematical operations                                                                                                                                                                                               
	matrix<T> operator+(const matrix<T>& rhs);
	matrix<T>& operator+=(const matrix<T>& rhs);
	matrix<T> operator-(const matrix<T>& rhs);
	matrix<T>& operator-=(const matrix<T>& rhs);
	matrix<T> operator*(const matrix<T>& rhs);
	matrix<T>& operator*=(const matrix<T>& rhs);
	matrix<T> operator% (const matrix<T>& rhs); // Hadamard product
	matrix<T> transpose();

	// Matrix/scalar operations                                                                                                                                                                                                     
	matrix<T> operator+(const T& rhs);
	matrix<T> operator-(const T& rhs);
	matrix<T> operator*(const T& rhs);
	matrix<T> operator/(const T& rhs);
	

	// Matrix/vector operations                                                                                                                                                                                                     
	std::vector<T> operator*(const std::vector<T>& rhs);
	std::vector<T> diag_vec();

	// Access the individual elements                                                                                                                                                                                               
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	// Returns sub-matrices
	matrix<T> sub_rows(std::vector<int> row_inds);
	matrix<T> sub_cols(std::vector<int> col_inds);

	// Access the row and column sizes                                                                                                                                                                                              
	unsigned get_rows() const;
	unsigned get_cols() const;

};

#include "matrix.cpp"

#endif