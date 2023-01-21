#ifndef MODEL_H_
#define MODEL_H_

#include "Matrix.hpp"
#include <vector>
#include <cmath>

double relu(double x)
{
    return x > 0 ? x : 0;
}
double d_relu(double x)
{
    return x > 0 ? 1 : 0;
}

double leaky_relu(double x)
{
    return x > 0 ? x : 0.1 * x;
}
double d_leaky_relu(double x)
{
    return x > 0 ? 1 : 0.1;
}

double step(double x)
{
    return x > 0 ? 1 : 0;
}
double d_step(double x)
{
    return x == 0 ? 1 : 0;
}

double sigmoid(double x)
{
    return 1 / (1 + std::exp(-x));
}
double d_sigmoid(double x)
{
    return std::exp(-x)/((std::exp(-x) + 1) * (std::exp(-x) + 1));
}

class Model {
private:
    int N{0};
    std::vector<Matrix> weights;
    std::vector<Matrix> biases;
    std::vector<double (*)(double)> activations;
    std::vector<double (*)(double)> d_activations;

public:
    Model(std::vector<int> layerSizes, std::vector<int> actFunc, double minVal = -1, double maxVal = 1)
    {
        N = layerSizes.size();
        for(int i = 0; i < N; i++)
        {
            if(i != N)
            {
                weights.push_back({layerSizes[i], layerSizes[i+1], minVal, maxVal});
                biases.push_back({layerSizes[i+1], 1, minVal, maxVal});
            }
            switch(actFunc[i])
            {
                case 1:
                    activations.push_back(&leaky_relu);
                    d_activations.push_back(&d_leaky_relu);
                    break;
                case 2:
                    activations.push_back(&step);
                    d_activations.push_back(&d_step);
                    break;
                case 3:
                    activations.push_back(&sigmoid);
                    d_activations.push_back(&d_sigmoid);
                    break;
                default:
                    activations.push_back(&relu);
                    d_activations.push_back(&d_relu);
                    break;
            }
        }
    }
    Matrix forwardPropagation(Matrix inputData)
    {
        int inputSize = inputData.getCols();
        auto w_n = weights.begin();
        auto b_n = biases.begin();
        auto f_n = activations.begin();
        inputData.applyFunc(*f_n);
        f_n++;

        for(int n = 0; n < N - 1; n++)
        {
            inputData = (*w_n) * inputData;
            inputData = (*b_n) * Matrix(1, inputSize, 1) + inputData;
            inputData.applyFunc(*f_n);
            w_n++;
            b_n++;
            f_n++;
        }
        return inputData;
    }
};

#endif