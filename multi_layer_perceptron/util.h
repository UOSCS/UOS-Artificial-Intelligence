// Class containing fields and member functions mainly used throughout the program

#ifndef UTIL_H
#define UTIL_H

#include "main.h"
#include "perceptron.h"
#include "gate.h"
#include "pGNUPlotU.h"

#define MAX_ITERATION 100000
#define CONVERGENCE 0.0000001
#define TOLERANCE 0.1

class My_Utils
{
    public:
        vector<vector<double>> inputs;

        vector<double> input;

        int num_of_layers;

        int num_of_nodes_of_layer;

        int dimension;

        int sequence;


        My_Utils();

        void get_dimension();

        void get_node_and_layer();

        void generate_inputs(int depth);

        CpGnuplotU* get_plot();

        void start_simulation(Perceptron& perceptron);

        void draw_error_point(ofstream& plot_output_file, double average_of_error, int num_of_iteration);

        void save_weights(string& class_name, vector<vector<vector<double>>>& weights);

        void draw_graph(string& plot_output_file_name);

        bool is_finished(int correct_count, int size_of_inputs);

        void stop_and_wait();
};

#endif