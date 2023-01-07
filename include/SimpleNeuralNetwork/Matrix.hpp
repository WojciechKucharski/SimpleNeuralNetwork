#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <cstring>
#include <algorithm>
#include <random>
#include <cmath>

class Matrix {
private:
    int rows;
    int cols;
    int rowSwaps{0};
    double *data;

public:
    // Size getters
    int getRows() const {return rows;}
    int getCols() const {return cols;}
    bool isEmpty() const {return data == nullptr ? true : false;}

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
        for (int i = 0; i < rows * cols; i++) result.data[i] = data[i] + other.data[i];
        return result;
    }

    // Subtraction operator
    Matrix operator-(const Matrix &other) const 
    {
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) result.data[i] = data[i] - other.data[i];
        return result;
    }

    // Addition operator
    Matrix operator+(double scalar) const
    {
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) result.data[i] = data[i] + scalar;
        return result;
    }

    // Subtraction operator
    Matrix operator-(double scalar) const 
    {
        Matrix result(rows, cols);
        for (int i = 0; i < rows * cols; i++) result.data[i] = data[i] - scalar;
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

    // Method for swapping rows
    void swapRows(int firstRow, int secondRow)
    {
        double tmp;
        for (int i = 0; i < cols; i++)
        {
            tmp = (*this)(firstRow, i);
            (*this)(firstRow, i) = (*this)(secondRow, i);
            (*this)(secondRow, i) = tmp;
        }
        rowSwaps++;
    }

    // Method for adding rows
    void addRows(int firstRow, int secondRow, double coeff)
    {
        for (int i = 0; i < cols; i++) (*this)(firstRow, i) += (*this)(secondRow, i) * coeff;
    }

    // Transpose Method
    Matrix transpose() const
    {
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

    // Det calculation
    double det() const
    {
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

    //Min Max
    double maxValue() const
    {
        double maxvalue = data[0];
        for(int i = 1; i < rows * cols; i++)
        {
            if (data[i] > maxvalue) maxvalue = data[i];
        }
        return maxvalue;
    }

    //Min Max
    double minValue() const
    {
        double minvalue = data[0];
        for(int i = 1; i < rows * cols; i++)
        {
            if (data[i] < minvalue) minvalue = data[i];
        }
        return minvalue;
    }

    //Normalise
    void normalise()
    {
        double min = minValue();
        double max = maxValue();
        min = min < 0 ? -min : min;
        double coeff = min > max ? min : max;

        for (int i = 0; i < rows * cols; i++) data[i] /= coeff;
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
    void printInfo() const
    {
        std::cout<<"Matix Info:\n";
        std::cout<<"Cols: " << cols << ", Rows: " << rows <<std::endl;
        std::cout<<"Max " << this->maxValue() << ", Min: " << this->minValue()<<std::endl;
    }
};

#endif