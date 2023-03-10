#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <cstring>
#include <algorithm>
#include <random>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
class Matrix {
private:
    int rows;
    int cols;
    int rowSwaps{0};
    double *data;

public:
    int getRows() const {return rows;}
    int getCols() const {return cols;}
    bool isEmpty() const {return data == nullptr ? true : false;}
    bool isValid() const {return !isEmpty() && rows > 0 && cols > 0;}
    bool isSquare() const {return isValid() && rows == cols;}
    bool isIdentity(double tol = 0.001) const
    {
        if(!isSquare()) return false;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if((i == j)){if((abs((*this)(i,j)-1) > tol)) return false;}
                else if((abs((*this)(i,j)) > tol)) return false;
            }
        }
        return true;
    }

    // Default constructor
    Matrix() : rows(0), cols(0), data(nullptr) {}

    // Constructor with size specified
    Matrix(int rows, int cols, double value = 0) : rows(rows), cols(cols)
    {
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++) data[i] = value;
    }

    // Copy constructor
    Matrix(const Matrix &other) : rows(other.rows), cols(other.cols)
    {
        data = new double[rows * cols];
        std::memcpy(data, other.data, rows * cols * sizeof(double));
    }

    // Random constructor
    Matrix(int rows, int cols, double minRand, double maxRand) : rows(rows), cols(cols)
    {
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++) data[i] = minRand + (double)rand() / RAND_MAX * (maxRand - minRand);
    }

    // Constructor from initializer list
    Matrix(std::initializer_list<std::initializer_list<double>> other) : rows(other.size()), cols((*other.begin()).size())
    {
        data = new double[rows * cols];
        int i = 0;
        for(auto it1 = other.begin(); it1 != other.end(); it1++)
        {
            for(auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
            {
                data[i] = *it2;
                i++;
            }
        }
    }

    ~Matrix() {
        delete[] data;
    } 

    // Access element at specified row and column
    double& operator()(int row, int col) 
    {
        isIndexValid(row, col);
        return data[row * cols + col];
    }

    // Access element at specified row and column (const version)
    const double& operator()(int row, int col) const 
    {
        isIndexValid(row, col);
        return data[row * cols + col];
    }

    void isIndexValid(int i, int j) const
    {
        if ((i < 0 || j < 0) || (i >= rows || j >= cols))
        {
            throw std::out_of_range("Matrix index (" + std::to_string(i) + ", " + std::to_string(j) + ") out of range, Matrix size (" + std::to_string(rows) + ", " + std::to_string(cols) + ")");
        }
    }

    // Assignment operator
    Matrix& operator=(const Matrix &other) 
    {
        if (this != &other) {
            // Only copy if other is a different matrix
            delete[] data;
            rows = other.rows;
            cols = other.cols;
            data = new double[rows * cols];
            std::memcpy(data, other.data, rows * cols * sizeof(double));
        }
        return *this;
    }

    // Addition operator
    Matrix operator+(const Matrix &other) const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        if(!other.isValid()) throw std::logic_error("Matrix not valid");
        if(rows != other.rows || cols != other.cols) throw std::logic_error("Cant add matrices (" + std::to_string(rows) + ", " + std::to_string(cols) + "), (" + std::to_string(other.rows) + ", " + std::to_string(other.cols) + ")");
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) result.data[i] = data[i] + other.data[i];
        return result;
    }

    // Subtraction operator
    Matrix operator-(const Matrix &other) const 
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        if(!other.isValid()) throw std::logic_error("Matrix not valid");
        if(rows != other.rows || cols != other.cols) throw std::logic_error("Cant subtract matrices (" + std::to_string(rows) + ", " + std::to_string(cols) + "), (" + std::to_string(other.rows) + ", " + std::to_string(other.cols) + ")");
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) result.data[i] = data[i] - other.data[i];
        return result;
    }

    // Addition operator
    Matrix operator+(double scalar) const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) result.data[i] = data[i] + scalar;
        return result;
    }

    // Subtraction operator
    Matrix operator-(double scalar) const 
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) result.data[i] = data[i] - scalar;
        return result;
    }

    // Multiplication operator
    Matrix operator*(const Matrix &other) const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        if(!other.isValid()) throw std::logic_error("Matrix not valid");
        if(cols != other.rows) throw std::logic_error("Cant multipy matrices (" + std::to_string(rows) + ", " + std::to_string(cols) + "), (" + std::to_string(other.rows) + ", " + std::to_string(other.cols) + ")");
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < other.cols; j++) 
            {
                result(i, j) = 0;
                for (int k = 0; k < cols; k++) 
                {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    // Scalar multiplication operator
    Matrix operator*(double scalar) const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) result.data[i] = data[i] * scalar;
        return result;
    }

    // Compare operator
    bool operator==(const Matrix &other) const 
    {
        if (rows != other.rows || cols != other.cols) return false;
        for (int i = 0; i < rows * cols; i++)
            if (data[i] != other.data[i]) return false;
        return true;
    }

    void swapRows(int firstRow, int secondRow)
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        isIndexValid(firstRow, 0);
        isIndexValid(secondRow, 0);
        double tmp;
        for (int i = 0; i < cols; i++)
        {
            tmp = (*this)(firstRow, i);
            (*this)(firstRow, i) = (*this)(secondRow, i);
            (*this)(secondRow, i) = tmp;
        }
        rowSwaps++;
    }

    // Vector getters
    Matrix getRow(int row) const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        isIndexValid(row, 0);
        Matrix result = {1, cols, 0};
        for(int i = 0; i < cols; i++) result(0, i) = (*this)(row, i);
        return result;
    }

    Matrix getCol(int row) const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        isIndexValid(0, row);
        Matrix result = {rows, 1, 0};
        for(int i = 0; i < rows; i++) result(i, 0) = (*this)(i, row);
        return result;
    }  

    void addRows(int firstRow, int secondRow, double factor)
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        isIndexValid(firstRow, 0);
        isIndexValid(secondRow, 0);
        for (int i = 0; i < cols; i++) (*this)(firstRow, i) += (*this)(secondRow, i) * factor;
    }

    void mulRow(int row, double factor)
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        isIndexValid(row, 0);
        for (int i = 0; i < cols; i++) (*this)(row, i) *= factor;
    }

    Matrix transpose() const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    double det() const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        if(!isSquare()) throw std::logic_error("Determinient only for Square Matrix");
        if(rows==1 || cols==1) return data[0];
        Matrix dummy = *this;
        double factor, det = 1;
        int h;

        for(int i = 0; i < rows - 1; i++){
            for(int j = 1; j < rows - i; j++){
                h = 1;
                while(dummy(i, i) == 0.0){
                    if(i == rows - h) return 0;
                    dummy.swapRows(i, rows - h);
                    h++;
                    }
                factor = dummy(i+j, i) / dummy(i, i);
                dummy.addRows(i + j, i, -factor);
            }
        }
        
        for(int i = 0; i < rows; i++) det *= dummy(i, i);
        return det * (dummy.rowSwaps % 2 ? -1 : 1);
    }

    Matrix reversed() const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        if(!isSquare()) throw std::logic_error("Reversion only for Square Matrix");
        Matrix dummy = *this;
        Matrix result = {rows, cols, 0};
        for(int i = 0; i < rows; i++) result(i,i) = 1;
        double factor;
        int h;

        for(int i = 0; i < rows - 1; i++){
            for(int j = 1; j < rows - i; j++)
            {
                h = 1;
                while(dummy(i, i) == 0.0){
                    if(i == rows - h) return {rows, cols, 0};
                    dummy.swapRows(i, rows - h);
                    result.swapRows(i, rows - h);
                    h++;
                    }
                factor = dummy(i+j, i) / dummy(i, i);
                dummy.addRows(i + j, i, -factor);
                result.addRows(i + j, i, -factor);
            }
        }
        for(int i = 0; i < rows; i++)
        {
            factor = dummy(i,i);
            dummy.mulRow(i, 1/factor);
            result.mulRow(i, 1/factor);
        }
        for(int i = rows - 1; i > 0; i--)
        {
            for(int j = 0; j < i; j++)
            {
                factor = dummy(j, i) / dummy(i, i);
                dummy.addRows(j, i, -factor);
                result.addRows(j, i, -factor);
            }
        }
        return result;
    }

    double maxValue() const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        double maxvalue = data[0];
        for(int i = 1; i < rows * cols; i++)
        {
            if (data[i] > maxvalue) maxvalue = data[i];
        }
        return maxvalue;
    }

    double minValue() const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        double minvalue = data[0];
        for(int i = 1; i < rows * cols; i++)
        {
            if (data[i] < minvalue) minvalue = data[i];
        }
        return minvalue;
    }

    void normalise()
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        double min = minValue();
        double max = maxValue();
        min = min < 0 ? -min : min;
        double coeff = min > max ? min : max;

        for (int i = 0; i < rows * cols; i++) data[i] /= coeff;
    }

    double sum() const
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        double result = 0;
        for(int i = 0; i < rows * cols; i++) result += data[i];
        return result;
    }

    void applyFunc(double (*funcPtr)(double))
    {
        if(!isValid()) throw std::logic_error("Matrix not valid");
        for(int i = 0; i < rows * cols; i++) data[i] = funcPtr(data[i]);
    }

    void printMatrix() const
    {
        for (int i = 0; i < rows; i++)
        {
            std::cout << "|";
            for (int j = 0; j < cols; j++)
            {
                std::cout << " " << data[i * cols + j];
            }
            std::cout << "| \n";
        }
    }
    void printInfo() const
    {
        std::cout<<"Matrix Info:\n";
        std::cout<< "Rows: " << rows <<", Cols: " << cols <<std::endl;
        std::cout<<"Max " << this->maxValue() << ", Min: " << this->minValue()<<std::endl;
    }
};

#endif