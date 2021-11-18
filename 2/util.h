// Class containing fields and member functions mainly used throughout the program

#ifndef UTIL_H
#define UTIL_H

#include "main.h"
#include "perceptron.h"
#include "gate.h"
#include "pGNUPlotU.h"

class My_Utils
{
    public:
        vector<vector<int>> inputs;
        vector<int> input;
        int dimension;
        int sequence;

        My_Utils();

        void get_dimension();

        void generate_inputs(int depth);

        void AND_OR_simulation(Perceptron& perceptron);

        void XOR_simulation(XOR_gate& xor_gate);

        void set_initial_point(CpGnuplotU *plot);

        void draw_graph(CpGnuplotU *plot, vector<double> &weights);

        void print_case(int index, int answer, double output, vector<double>& weights);

        void print_result(double output, int answer);

        bool is_correct(double output, int answer);

        void print_summary(int count_correct);

        bool is_finished(int count_correct);

        void stop_and_wait();
};

#endif