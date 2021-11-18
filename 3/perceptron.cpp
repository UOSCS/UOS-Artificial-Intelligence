#include "perceptron.h"

Perceptron::Perceptron(int num_of_layers, int num_of_nodes_of_layer, int dimension, vector<vector<double>>& inputs)
{
    this->num_of_layers = num_of_layers;

    this->num_of_nodes_of_layer = num_of_nodes_of_layer;

    total_layers = num_of_layers + 2;

    nets.resize(total_layers);

    outputs.resize(total_layers);

    weights.resize(total_layers - 1);

    deltas.resize(total_layers);

    generate_initial_weights(dimension);
}

void Perceptron::generate_initial_weights(int dimension)
{
    vector<int> num_of_nodes_of_layers;

    // input layer
    num_of_nodes_of_layers.push_back(dimension);

    // hidden layer
    for (int i = 0; i < num_of_layers; i++)
        num_of_nodes_of_layers.push_back(num_of_nodes_of_layer);

    // output layer
    num_of_nodes_of_layers.push_back(1);

    // resize weights
    // weight : [size of layer i + 1, (size of layer i) + 1] matrix
    for (size_t i = 0; i < weights.size(); i++)
        weights[i].resize(num_of_nodes_of_layers[i + 1], vector<double>(num_of_nodes_of_layers[i] + 1));

    srand(time(NULL));

    // initialize weights
    for (size_t i = 0; i < weights.size(); i++)
        for (size_t j = 0; j < weights[i].size(); j++)
            for (size_t k = 0; k < weights[i][j].size(); k++)
                weights[i][j][k] = RANDOM();
}

double Perceptron::sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

double Perceptron::sigmoid_differential_function(double x)
{
    return sigmoid(x) * (1.0 - sigmoid(x));
}

double Perceptron::activation_function(double net)
{
    // sigmoid
    return sigmoid(net);
}

void Perceptron::forward_propagation(vector<double> &input)
{
    // outputs[0] is input layer
    outputs[0] = input;

    // forward propagation
    for (size_t i = 0; i < weights.size(); i++)
        // calculate outputs[i + 1] using outputs[i]
        go_next_layer(outputs[i], i + 1);
}

void Perceptron::go_next_layer(vector<double> &prev_output, int output_sequence)
{
    // outputs vary according to each loop
    // a little later, will add net to output using push_back(), so need to clear it before calculate new nets
    // if not, length of output is getting longer and longer
    outputs[output_sequence].clear();

    // bias unit
    if (output_sequence != weights.size())
    {
        outputs[output_sequence].push_back(1);

        nets[output_sequence].push_back(1);
    }

    // weight * prev_output = nets of next layer
    // activation_function(net) = output
    // I miss matlab...
    for (size_t row = 0; row < weights[output_sequence - 1].size(); row++)
    {
        double net = 0.0;

        for (size_t column = 0; column < weights[output_sequence - 1][row].size(); column++)
            net += prev_output[column] * weights[output_sequence - 1][row][column];

        nets[output_sequence].push_back(net);

        outputs[output_sequence].push_back(activation_function(net));
    }
}

vector<double> Perceptron::get_delta_of_output_layer(double last_output, int input_sequence, int dimension, vector<double> &input)
{
    vector<double> output_layer_delta(1, last_output - get_answer(input_sequence, dimension, input));

    return output_layer_delta;
}

void Perceptron::back_propagation()
{
    // compute deltas
    for (size_t i = deltas.size() - 2; i >= 1; i--)
        deltas[i] = calc_delta(i);
}

vector<double> Perceptron::calc_delta(int layer)
{
    vector<double> delta;

    // column start with 1
    // throw away delta_0 on each layer
    for (size_t column = 1; column < weights[layer][0].size(); column++)
    {
        double delta_i = 0;

        for (size_t row = 0; row < weights[layer].size(); row++)
            delta_i += weights[layer][row][column] * deltas[layer + 1][row];

        delta_i *= sigmoid_differential_function(nets[layer][column]);

        delta.push_back(delta_i);
    }

    return delta;
}

void Perceptron::update_weights()
{
    // update weights
    for (size_t i = 0; i < weights.size(); i++)
        update_weight(i);
}

void Perceptron::update_weight(int layer)
{
    for (size_t row = 0; row < weights[layer].size(); row++)
        for (size_t column = 0; column < weights[layer][row].size(); column++)
            weights[layer][row][column] -= LEARNING_RATE * deltas[layer + 1][row] * outputs[layer][column];
}