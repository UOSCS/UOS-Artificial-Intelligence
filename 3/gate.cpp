#include "gate.h"

AND_gate::AND_gate(int num_of_layers, int num_of_nodes_of_layer, int dimension, vector<vector<double>>& inputs) : Perceptron(num_of_layers, num_of_nodes_of_layer, dimension, inputs) {}

OR_gate::OR_gate(int num_of_layers, int num_of_nodes_of_layer, int dimension, vector<vector<double>>& inputs) : Perceptron(num_of_layers, num_of_nodes_of_layer, dimension, inputs) {}

XOR_gate::XOR_gate(int num_of_layers, int num_of_nodes_of_layer, int dimension, vector<vector<double>>& inputs) : Perceptron(num_of_layers, num_of_nodes_of_layer, dimension, inputs) {}

Donut::Donut(int num_of_layers, int num_of_nodes_of_layer, int dimension, vector<vector<double>>& inputs) : Perceptron(num_of_layers, num_of_nodes_of_layer, dimension, inputs) {}

double AND_gate::get_answer(int index, int dimension, vector<double> &input)
{
    // AND gate
    return (index == (1 << dimension) - 1) ? 1.0 : 0.0;
}

double OR_gate::get_answer(int index, int dimension, vector<double> &input)
{
    // OR gate
    return (index != 0) ? 1.0 : 0.0;
}

double XOR_gate::get_answer(int index, int dimension, vector<double> &input)
{
    int num_of_1 = 0;

    for (int i = 1; i <= dimension; i++)
        if (input[i])
            num_of_1++;

    // XOR gate
    return (num_of_1 & 1) ? 1.0 : 0.0;
}

double Donut::get_answer(int index, int dimension, vector<double>& input)
{
    return (index < 8) ? 0.0 : 1.0;
}