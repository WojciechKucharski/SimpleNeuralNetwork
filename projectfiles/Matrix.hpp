#pragma once
#include <iostream>
#include <cstring>
#include <algorithm>

class Matrix {
private:
    int rows;
    int cols;
    double *data;

public:
    // Default constructor
    Matrix() : rows(0), cols(0), data(nullptr) {}

    // Constructor with size specified
    Matrix(int rows, int cols, double value = 0) : rows(rows), cols(cols)
    {
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; i++)
        {
            data[i] = value;
        }
    }

    // Copy constructor
    Matrix(const Matrix &other) : rows(other.rows), cols(other.cols)
    {
        data = new double[rows * cols];
        std::memcpy(data, other.data, rows * cols * sizeof(double));
    }

    // Destructor
    ~Matrix() {
        delete[] data;
    }

    // Access element at specified row and column
    double& operator()(int row, int col) 
    {
        return data[row * cols + col];
    }

    // Access element at specified row and column (const version)
    const double& operator()(int row, int col) const 
    {
        return data[row * cols + col];
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
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++)
        {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Subtraction operator
    Matrix operator-(const Matrix &other) const 
    {
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) 
        {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Multiplication operator
    Matrix operator*(const Matrix &other) const
    {
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
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++)
        {
            result.data[i] *= result.data[i] * scalar;
        }
        return result;
    }

    // Print matrix method
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
};