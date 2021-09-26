// Gate classes
// Extend perceptron class

#ifndef GATE_H
#define GATE_H

#include "main.h"
#include "perceptron.h"

class AND_gate : public Perceptron
{
    public:
        virtual int get_answer(int index, int dimension, vector<int> &input) override;
};

class OR_gate : public Perceptron
{
    public:
        virtual int get_answer(int index, int dimension, vector<int> &input) override;
};

class XOR_gate : public Perceptron
{
    public:
        vector<double> hidden_layer_weights;

        void generate_hidden_layer_weights(int dimension);

        virtual int get_answer(int index, int dimension, vector<int> &input) override;

        int hidden_layer_activation_function(double net);

        vector<int> hidden_layer(int dimension, vector<int> &input);
};

#endif