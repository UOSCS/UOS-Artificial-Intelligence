#include "main.h"
#include "util.h"
#include "perceptron.h"
#include "gate.h"
#include "pGNUPlotU.h"

int main(void)
{
    ios::sync_with_stdio(0);

    My_Utils util;

    util.get_node_and_layer();

    // AND gate
    AND_gate and_gate(util.num_of_layers, util.num_of_nodes_of_layer, util.dimension, util.inputs);

    util.start_simulation(and_gate);

    util.stop_and_wait();

    // OR gate
    OR_gate or_gate(util.num_of_layers, util.num_of_nodes_of_layer, util.dimension, util.inputs);

    util.start_simulation(or_gate);

    util.stop_and_wait();

    // XOR gate
    XOR_gate xor_gate(util.num_of_layers, util.num_of_nodes_of_layer, util.dimension, util.inputs);

    util.start_simulation(xor_gate);

    util.stop_and_wait();

    // donut
    // generate new inputs
    vector<vector<double>> donut_inputs = {
        {1., 0., 0.},
        {1., 0., 1.},
        {1., 1., 0.},
        {1., 1., 1.},
        {1., 0.5, 1.},
        {1., 1., 0.5},
        {1., 0., 0.5},
        {1., 0.5, 0.},
        {1., 0.5, 0.5}};

    util.inputs.clear();

    util.inputs = donut_inputs;

    Donut donut(util.num_of_layers, util.num_of_nodes_of_layer, util.inputs[0].size() - 1, util.inputs);

    util.start_simulation(donut);


    return 0;
}