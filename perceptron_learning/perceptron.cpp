#include "perceptron.h"

void Perceptron::generate_weights(int dimension)
{
    srand(time(NULL));

    for (int i = 0; i <= dimension; i++)
        weights.push_back(RANDOM());
}

int Perceptron::activation_function(double net)
{
    // Hard limiting
    return (net > 0.0) ? 1 : 0;
}

double Perceptron::get_output(int dimension, vector<int>& input, vector<double>& weights)
{
    double sum = 0.0;

    // Inner product
    for (int i = 0; i <= dimension; i++)
        sum += (double) input[i] * weights[i];

    return sum;
}

void Perceptron::do_learning(vector<int> &input, vector<double> &weights, int dimension, int delta)
{
    for (int i = 0; i <= dimension; i++)
        weights[i] += LEARNING_RATE * delta * input[i];
}