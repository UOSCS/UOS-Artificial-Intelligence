// Class that contains functions that are mainly used in perceptron
// The parent class of the gates

#ifndef PERCEPTRON_H
#define PERCEPTRON_H

// -160.0 ~ 167.67
#define RANDOM() (((double) rand() / 100.0) - 160.0)

#define LEARNING_RATE 3.0

#include "main.h"

class Perceptron
{
    public:
        vector<double> weights;

        void generate_weights(int dimension);

        int activation_function(double net);

        double get_output(int dimension, vector<int>& input, vector<double> &weights);

        void do_learning(vector<int> &input, vector<double> &weights, int dimension, int delta);

        virtual int get_answer(int index, int dimension, vector<int> &input) = 0;
};

#endif