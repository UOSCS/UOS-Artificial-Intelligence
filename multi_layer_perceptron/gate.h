// Gate classes
// Extend perceptron class

#ifndef GATE_H
#define GATE_H

#include "main.h"
#include "perceptron.h"

class AND_gate : public Perceptron
{
    public:
        AND_gate(int num_of_layers, int num_of_nodes_of_layer, int dimension, vector<vector<double>>& inputs);

        virtual double get_answer(int index, int dimension, vector<double> &input) override;
};

class OR_gate : public Perceptron
{
    public:
        OR_gate(int num_of_layers, int num_of_nodes_of_layer, int dimension, vector<vector<double>>& inputs);

        virtual double get_answer(int index, int dimension, vector<double> &input) override;
};

class XOR_gate : public Perceptron
{
    public:
        XOR_gate(int num_of_layers, int num_of_nodes_of_layer, int dimension, vector<vector<double>>& inputs);

        virtual double get_answer(int index, int dimension, vector<double> &input) override;
};

class Donut : public Perceptron
{
    public:
        Donut(int num_of_layers, int num_of_nodes_of_layer, int dimension, vector<vector<double>>& inputs);

        virtual double get_answer(int index, int dimension, vector<double>& input) override;
};

#endif