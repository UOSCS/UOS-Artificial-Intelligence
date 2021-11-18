// Class that contains functions that are mainly used in perceptron
// The parent class of the gates

#ifndef PERCEPTRON_H
#define PERCEPTRON_H

// -16.0 ~ 16.767
#define RANDOM() (((double) rand() / 1000.0) - 16.0)

#define LEARNING_RATE 2.0

#include "main.h"

class Perceptron
{
    public:

        int num_of_layers;

        int num_of_nodes_of_layer;

        vector<vector<double>> nets;

        vector<vector<double>> outputs;

        vector<vector<vector<double>>> weights;

        vector<vector<double>> deltas;

        int total_layers;


        Perceptron(int num_of_layers, int num_of_nodes_of_layer, int dimension, vector<vector<double>>& inputs);

        double sigmoid(double x);

        double sigmoid_differential_function(double x);

        void generate_initial_weights(int dimension);

        double activation_function(double net);

        void forward_propagation(vector<double> &input);

        void go_next_layer(vector<double>& prev_output, int output_sequence);

        vector<double> get_delta_of_output_layer(double last_output, int input_sequence, int dimension, vector<double>& input);

        void back_propagation();

        vector<double> calc_delta(int index);

        void update_weights();

        void update_weight(int index);

        virtual double get_answer(int index, int dimension, vector<double> &input) = 0;
};

#endif