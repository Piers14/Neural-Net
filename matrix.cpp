#ifndef __MATRIX_CPP
#define __MATRIX_CPP

#include "matrix.h"

template<typename T>
matrix<T>::matrix()
{
    cols = 0;
    rows = 0;
}

// Parameter Constructor                                                                                                                                                      
template<typename T>
matrix<T>::matrix(unsigned _rows, unsigned _cols, const T& _initial) {
    mat.resize(_rows);
    for (unsigned i = 0; i < mat.size(); i++) {
        mat[i].resize(_cols, _initial);
    }
    rows = _rows;
    cols = _cols;
}

template<typename T>
matrix<T>::matrix(unsigned _rows, unsigned _cols, const std::vector<T> _vec)
{
    assert(_vec.size() == (_rows * _cols));
    mat.resize(_rows);
    for (unsigned i = 0; i < _rows; i++) {
        mat[i].resize(_cols);
    }
    unsigned k = 0;
    for (unsigned i = 0; i < _rows; i++) {
        for (unsigned j = 0; j < _cols; j++) {
            mat[i][j] = _vec[k];
            k++;
        }
    }
    rows = _rows;
    cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
matrix<T>::matrix(const matrix<T>& rhs) {
    mat = rhs.mat;
    rows = rhs.get_rows();
    cols = rhs.get_cols();
}

// (Virtual) Destructor                                                                                                                                                       
template<typename T>
matrix<T>::~matrix() {}

template<typename T>
void matrix<T>::resize(unsigned new_rows, unsigned new_cols)
{
    mat.resize(new_rows);
    for (unsigned i = 0; i < mat.size(); i++) {
        mat[i].resize(new_cols);
    }
    rows = new_rows;
    cols = new_cols;
}

// Assignment Operator                                                                                                                                                        
template<typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& rhs) {
    if (&rhs == this)
        return *this;

    unsigned new_rows = rhs.get_rows();
    unsigned new_cols = rhs.get_cols();

    mat.resize(new_rows);
    for (unsigned i = 0; i < mat.size(); i++) {
        mat[i].resize(new_cols);
    }

    for (unsigned i = 0; i < new_rows; i++) {
        for (unsigned j = 0; j < new_cols; j++) {
            mat[i][j] = rhs(i, j);
        }
    }
    rows = new_rows;
    cols = new_cols;

    return *this;
}

// Insertion operator
template<typename T>
std::ostream& operator<<(std::ostream& output, const matrix<T>& rhs) {
    for (unsigned i = 0; i < rhs.rows; i++) {
        for (unsigned j = 0; j < rhs.cols; j++) {
            output << std::setprecision(4) << std::scientific << rhs(i, j) << "  ";
        }
        output << "\b\b" << std::endl;
    }
    output << std::endl;
    return output;
}


// Addition of two matrices                                                                                                                                                   
template<typename T>
matrix<T> matrix<T>::operator+(const matrix<T>& rhs) {
    matrix result(rows, cols, 0.0);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            result(i, j) = this->mat[i][j] + rhs(i, j);
        }
    }

    return result;
}

// Cumulative addition of this matrix and another                                                                                                                             
template<typename T>
matrix<T>& matrix<T>::operator+=(const matrix<T>& rhs) {
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            this->mat[i][j] += rhs(i, j);
        }
    }

    return *this;
}

// Subtraction of this matrix and another                                                                                                                                     
template<typename T>
matrix<T> matrix<T>::operator-(const matrix<T>& rhs) {
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();
    matrix result(rows, cols, 0.0);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            result(i, j) = this->mat[i][j] - rhs(i, j);
        }
    }

    return result;
}

// Cumulative subtraction of this matrix and another                                                                                                                          
template<typename T>
matrix<T>& matrix<T>::operator-=(const matrix<T>& rhs) {
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            this->mat[i][j] -= rhs(i, j);
        }
    }

    return *this;
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
matrix<T> matrix<T>::operator*(const matrix<T>& rhs) {
    assert(this->get_cols() == rhs.get_rows());
    unsigned rows = this->get_rows();
    unsigned cols = rhs.get_cols();
    matrix result(rows, cols, 0.0);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            for (unsigned k = 0; k < this->get_cols(); k++) {
                result(i, j) += this->mat[i][k] * rhs(k, j);
            }
        }
    }

    return result;
}

// Cumulative left multiplication of this matrix and another                                                                                                                  
template<typename T>
matrix<T>& matrix<T>::operator*=(const matrix<T>& rhs) {
    matrix result = (*this) * rhs;
    (*this) = result;
    return *this;
}

template<typename T>
matrix<T> matrix<T>::operator% (const matrix<T>& rhs)
{
    matrix result(rows, cols, 0);
    for (unsigned i = 0; i < rows; i++)
    {
        for (unsigned j = 0; j < cols; j++)
        {
            result(i, j) = this->mat[i][j] * rhs(i, j);
        }
    }
    return result;
}

// Calculate a transpose of this matrix                                                                                                                                       
template<typename T>
matrix<T> matrix<T>::transpose() {
    matrix result;
    result.resize(cols, rows);

    for (unsigned i = 0; i < cols; i++) {
        for (unsigned j = 0; j < rows; j++) {
            result(i, j) = this->mat[j][i];
        }
    }

    return result;
}

// Matrix/scalar addition                                                                                                                                                     
template<typename T>
matrix<T> matrix<T>::operator+(const T& rhs) {
    matrix result(rows, cols, 0.0);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            result(i, j) = this->mat[i][j] + rhs;
        }
    }

    return result;
}

// Matrix/scalar subtraction                                                                                                                                                  
template<typename T>
matrix<T> matrix<T>::operator-(const T& rhs) {
    matrix result(rows, cols, 0.0);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            result(i, j) = this->mat[i][j] - rhs;
        }
    }

    return result;
}

// Matrix/scalar multiplication                                                                                                                                               
template<typename T>
matrix<T> matrix<T>::operator*(const T& rhs) {
    matrix result(rows, cols, 0.0);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            result(i, j) = this->mat[i][j] * rhs;
        }
    }

    return result;
}

// Matrix/scalar division                                                                                                                                                     
template<typename T>
matrix<T> matrix<T>::operator/(const T& rhs) {
    matrix result(rows, cols, 0.0);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            result(i, j) = this->mat[i][j] / rhs;
        }
    }

    return result;
}

// Multiply a matrix with a vector                                                                                                                                            
template<typename T>
std::vector<T> matrix<T>::operator*(const std::vector<T>& rhs) {
    std::vector<T> result(rhs.size(), 0.0);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            result[i] = this->mat[i][j] * rhs[j];
        }
    }

    return result;
}

// Obtain a vector of the diagonal elements                                                                                                                                   
template<typename T>
std::vector<T> matrix<T>::diag_vec() {
    std::vector<T> result(rows, 0.0);

    for (unsigned i = 0; i < rows; i++) {
        result[i] = this->mat[i][i];
    }

    return result;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& matrix<T>::operator()(const unsigned& row, const unsigned& col) {
    assert(row < this->rows&& col < this->cols);
    return this->mat[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& matrix<T>::operator()(const unsigned& row, const unsigned& col) const {
    return this->mat[row][col];
}

template<typename T>
matrix<T> matrix<T>::sub_rows(std::vector<int> row_inds)
{
    matrix<T> result;
    result.resize(row_inds.size(), cols);
    for (unsigned i = 0; i < row_inds.size(); i++)
    {
        assert(row_inds[i] < rows);
        for (unsigned j = 0; j < cols; j++)
        {
            result.mat[i][j] = this->mat[row_inds[i]][j];
        }
    }
    return result;
}

template<typename T>
matrix<T> matrix<T>::sub_cols(std::vector<int> col_inds)
{
    matrix<T> result;
    result.resize(rows, col_inds.size());
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < col_inds.size(); j++)
        {
            assert(col_inds[j] < cols);
            result.mat[i][j] = this->mat[i][col_inds[j]];
        }
    }
    return result;
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned matrix<T>::get_rows() const {
    return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned matrix<T>::get_cols() const {
    return this->cols;
}

template<typename T>
matrix<double> matrix<T>::row_means()
{
    matrix<double> output(this->get_rows(), 1, 0);
    for (unsigned i = 0; i < this->get_rows(); i++)
    {
        for (unsigned j = 0; j < this->get_cols(); j++)
        {
            output(i, 0) += this->mat[i][j];
        }
    }
    output = output / this->get_cols();
    return output;
}

template<typename T>
matrix<double> matrix<T>::col_means()
{
    matrix<double> output(1, this->get_cols(), 0);
    for (unsigned i = 0; i < this->get_cols(); i++)
    {
        for (unsigned j = 0; j < this->get_rows(); j++)
        {
            output(0, i) += this->mat[j][i];
        }
    }
    output = output / this->get_rows();
    return output;
}


#endif