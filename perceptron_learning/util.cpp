#include "util.h"
#include "pGNUPlotU.h"
#include <sstream>
#include <direct.h>

My_Utils::My_Utils()
{
    get_dimension();

    inputs.resize(1 << dimension);

    input.resize(dimension);

    sequence = 0;
}

void My_Utils::get_dimension()
{
    cout << "Enter the dimension: ";

    cin >> dimension;

    cout << "\n\n";
}

void My_Utils::generate_inputs(int depth)
{
    if (depth == dimension)
    {
        inputs[sequence].push_back(1);

        for (int i = 0; i < dimension; i++)
            inputs[sequence].push_back(input[i]);

        sequence++;

        return;
    }

    input[depth] = 0;
    generate_inputs(depth + 1);

    input[depth] = 1;
    generate_inputs(depth + 1);
}

CpGnuplotU* get_plot()
{
    char current_dir[1000];

    // Get current working directory
    if (!_getcwd(current_dir, 1000))
    {
        perror("ERROR: Get current directory error!");

        exit(3);
    }

    // char * -> string
    string str(current_dir);

    // Make full path
    string path = str + "\\gnuplot\\bin\\wgnuplot.exe";

    // string -> wchar_t
    return new CpGnuplotU(wstring(path.begin(), path.end()).c_str());
}

void My_Utils::AND_OR_simulation(Perceptron& perceptron)
{
    // Setting for drawing graph
    CpGnuplotU *plot = get_plot();

    set_initial_point(plot);

    perceptron.generate_weights(dimension);

    while (true)
    {
        int count_correct = 0;

        // Test all inputs
        for (int i = 0; i < (1LL << dimension); i++)
        {
            double output = perceptron.get_output(dimension, inputs[i], perceptron.weights);

            bool answer = perceptron.get_answer(i, dimension, inputs[i]);

            print_case(i, answer, output, perceptron.weights);

            print_result(output, answer);

            if (is_correct(output, answer)) count_correct++;
            else perceptron.do_learning(inputs[i], perceptron.weights, dimension, answer - (output > 0.0 ? 1 : 0));
        }

        print_summary(count_correct);

        // Graph drawn only when dimension == 2
        if (dimension == 2)
            draw_graph(plot, perceptron.weights);

        if (is_finished(count_correct)) break;
    }

    delete plot;
}

void My_Utils::XOR_simulation(XOR_gate& xor_gate)
{
    // Setting for drawing graph
    CpGnuplotU* plot = get_plot();

    // For the special situation of XOR gate
    plot->cmd(L"set object circle at first 0, 0");

    plot->cmd(L"set object circle at first 1, 1");

    // In order to linearly separate the XOR gate, a hidden layer is required
    // So generate weights for hidden layer
    xor_gate.generate_hidden_layer_weights(dimension);

    xor_gate.generate_weights(2);

    while (true)
    {
        int count_correct = 0;

        // Test all inputs
        for (int i = 0; i < (1 << dimension); i++)
        {
            // Going through the hidden layer
            vector<int> hidden_layer_output = xor_gate.hidden_layer(dimension, inputs[i]);

            double output = xor_gate.get_output(2, hidden_layer_output, xor_gate.weights);

            bool answer = xor_gate.get_answer(i, dimension, inputs[i]);

            print_case(i, answer, output, xor_gate.weights);

            print_result(output, answer);

            if (is_correct(output, answer)) count_correct++;
            else xor_gate.do_learning(hidden_layer_output, xor_gate.weights, 2, answer - (output > 0.0 ? 1 : 0));
        }

        print_summary(count_correct);

        // Graph drawn only when dimension == 2
        if (dimension == 2)
            draw_graph(plot, xor_gate.weights);

        if (is_finished(count_correct)) break;
    }

    delete plot;
}

// Only for AND, OR gate
void My_Utils::set_initial_point(CpGnuplotU *plot)
{
    plot->cmd(L"set object circle at first 0, 0");
    plot->cmd(L"set object circle at first 0, 1");
    plot->cmd(L"set object circle at first 1, 0");
    plot->cmd(L"set object circle at first 1, 1");
}

void My_Utils::draw_graph(CpGnuplotU *plot, vector<double> &weights)
{
    // Calculate the slope
    double slope = -weights[1] / weights[2];

    // Calculate the y-intercept
    double y_intercept = -weights[0] / weights[2];

    // Make a straight graph formula
    string command = "plot [x=-3:3] [y=-3:3] " + to_string(slope) + "*x+" + to_string(y_intercept);

    // 1. Transfer string -> wchar_t
    // 2. Move on to the argument of plot.cmd drawing graph
    plot->cmd(wstring(command.begin(), command.end()).c_str());

    // Stop and wait to check gnuplot
    stop_and_wait();
}

void My_Utils::print_case(int index, int answer, double output, vector<double> &weights)
{
    cout << "Case " << index + 1 << ": ";

    for (int i = 0; i <= dimension; i++)
        cout << inputs[index][i];

    cout << "\n\tWeights: ";

    for (size_t i = 0; i < weights.size(); i++)
        cout << "W" << i << " " << weights[i] << ", ";

    cout << "\n\tAnswer: " << answer;

    cout << "\n\tNet   : " << output;

    cout << "\n\tResult: ";
}

void My_Utils::print_result(double output, int answer)
{
    if ((output > 0 && answer) || (output <= 0 && !answer))
        cout << "CORRECT!!\n\n";
    else
        cout << "OH MY GOD\n\n";
}

bool My_Utils::is_correct(double output, int answer)
{
    if ((output > 0 && answer) || (output <= 0 && !answer))
        return true;
    else
        return false;
}

void My_Utils::print_summary(int count_correct)
{
    cout << "\nNumber of Correct Cases: " << count_correct << " (Expected: " << (1 << dimension) << ")\n";

    if (count_correct == 1 << dimension)
        cout << "\n\nFinally Finished :)\n\n\n";
    else
        cout << "\n\nTry Again...\n\n\n";
}

bool My_Utils::is_finished(int count_correct)
{
    if (count_correct == 1 << dimension)
        return true;
    else
        return false;
}

void My_Utils::stop_and_wait()
{
    char tmp;

    cout << "\nEnter any key to continue...\n";

    cin >> tmp;
}