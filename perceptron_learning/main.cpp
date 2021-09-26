#include "main.h"
#include "util.h"
#include "perceptron.h"
#include "gate.h"
#include "pGNUPlotU.h"

int main(void)
{
    My_Utils util;

    // Generate (2^dimension) inputs
    // Each input's length will be (dimension + 1).
    util.generate_inputs(0);

    // AND gate
    AND_gate and_gate;
    util.AND_OR_simulation(and_gate);

    util.stop_and_wait();

    // OR gate
    OR_gate or_gate;
    util.AND_OR_simulation(or_gate);

    util.stop_and_wait();

    // XOR gate
    XOR_gate xor_gate;
    util.XOR_simulation(xor_gate);

    return 0;
}