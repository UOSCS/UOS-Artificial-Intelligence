#include "gate.h"

int AND_gate::get_answer(int index, int dimension, vector<int> &input)
{
    // AND gate
    return (index == (1 << dimension) - 1) ? 1 : 0;
}

int OR_gate::get_answer(int index, int dimension, vector<int> &input)
{
    // OR gate
    return (index != 0) ? 1 : 0;
}

int XOR_gate::get_answer(int index, int dimension, vector<int> &input)
{
    int num_of_1 = 0;

    for (int i = 1; i <= dimension; i++)
        if (input[i])
            num_of_1++;

    // XOR gate
    return (num_of_1 & 1) ? 1 : 0;
}

void XOR_gate::generate_hidden_layer_weights(int dimension)
{
    // The size of the hidden layer's weights is same with input's
    hidden_layer_weights.resize(dimension + 1);

    // weights = {1, 1, 1, ...}
    fill(hidden_layer_weights.begin(), hidden_layer_weights.end(), 1);

    // weights = {0, 1, 1, ...}
    hidden_layer_weights[0] = 0;
}

int XOR_gate::hidden_layer_activation_function(double net)
{
    // If the number of 1 of input is odd, activated to become 1
    return ((int) net & 1) ? 1 : 0;
}

vector<int> XOR_gate::hidden_layer(int dimension, vector<int> &input)
{
    // In hidden layer, if the number of 1 of input is odd, both nodes of the hidden layer are activated to become 1
    // Two nodes of the hidden layer have same weights
    // So check activation function only once, not twice -> generate output
    if (hidden_layer_activation_function(get_output(dimension, input, hidden_layer_weights)))
        return { 1, 1, 1 };
    else
        return { 1, 0, 0 };
}