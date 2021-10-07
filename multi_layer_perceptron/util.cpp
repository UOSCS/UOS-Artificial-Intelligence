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

    generate_inputs(0);
}

void My_Utils::get_dimension()
{
    cout << "Enter the dimension: ";

    cin >> dimension;

    cout << "\n\n";
}

void My_Utils::get_node_and_layer()
{
    cout << "Enter the number of hidden layers: ";

    cin >> num_of_layers;

    cout << "\nEnter the number of nodes of hidden layer: ";

    cin >> num_of_nodes_of_layer;

    cout << "\n\n";
}

void My_Utils::generate_inputs(int depth)
{
    if (depth == dimension)
    {
        inputs[sequence].push_back(1.0);

        for (int i = 0; i < dimension; i++)
            inputs[sequence].push_back(input[i]);

        sequence++;

        return;
    }

    input[depth] = 0.0;
    generate_inputs(depth + 1);

    input[depth] = 1.0;
    generate_inputs(depth + 1);
}

CpGnuplotU* My_Utils::get_plot()
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

void My_Utils::start_simulation(Perceptron& perceptron)
{
    int current_iteration = 1;

    double prev_average_of_error = 1.0;
        
    double current_average_of_error;

    string class_name(typeid(perceptron).name());

    string plot_output_file_name(".\\" + class_name + "_plot.txt");

    // file of coordinates
    ofstream plot_output_file(plot_output_file_name);

    while (true)
    {
        int correct_count = 0;

        double sum_of_error = 0.0;

        for (size_t i = 0; i < inputs.size(); i++)
        {
            // forward propagation
            perceptron.forward_propagation(inputs[i]);

            // get last output
            double last_output = perceptron.outputs.back().front();

            // get delta of output layer that is starting point of  back propagation
            perceptron.deltas[perceptron.deltas.size() - 1] = perceptron.get_delta_of_output_layer(last_output, i, dimension, inputs[i]);

            // backward propagation
            perceptron.back_propagation();

            // update weights
            perceptron.update_weights();

            // calculate sum of error
            double output_layer_error = abs(perceptron.deltas.back().front());

            sum_of_error += output_layer_error;

            // count when delta of output layer is less than TOLERANCE
            if (output_layer_error < TOLERANCE)
                correct_count++;
        }

        // average of error of current epoch
        current_average_of_error = sum_of_error / (double)inputs.size();

        // print the average of error
        cout << "Error: " << current_average_of_error << "\n";

        // add (iteration, error) point to plot file
        draw_error_point(plot_output_file, current_average_of_error, current_iteration);

        // checking is possible for escaping from loop
        if (is_finished(correct_count, inputs.size())) break;
        
        // newly reset the weights when
        // 1) current iteration exceeds MAX_ITERATION
        // 2) error converges but not less than TOLERANCE
        if (++current_iteration > MAX_ITERATION || abs(prev_average_of_error - current_average_of_error) < CONVERGENCE)
        {
            cout << "NEWLY RESET THE WEIGHTS!!!" << '\n';

            perceptron.generate_initial_weights(dimension);

            // new iteration
            current_iteration = 1;

            // new plot
            plot_output_file.close();
       
            plot_output_file.open(plot_output_file_name);
        }

        // current becomes prev for next loop
        prev_average_of_error = current_average_of_error;
    }
    
    // finally find correct weights
    // save weights
    save_weights(class_name, perceptron.weights);

    // save points
    plot_output_file.close();

    // draw error graph
    draw_graph(plot_output_file_name);
}

void My_Utils::draw_error_point(ofstream& plot_output_file, double average_of_error, int num_of_iteration)
{
    plot_output_file << num_of_iteration << ' ' << average_of_error << '\n';
}

void My_Utils::save_weights(string& class_name, vector<vector<vector<double>>>& weights)
{
    string weights_output_file_name(".\\" + class_name + "_weights.txt");

    ofstream weights_output_file(weights_output_file_name);

    ostream_iterator<double> weights_output_iterator(weights_output_file, " ");

    for (vector<vector<double>> weight : weights)
    {
        for (vector<double> row : weight)
        {
            copy(row.begin(), row.end(), weights_output_iterator);

            weights_output_file << '\n';
        }
        weights_output_file << '\n';
    }

    weights_output_file.close();
}

void My_Utils::draw_graph(string& plot_output_file_name)
{
    // gnuplot
    CpGnuplotU* plot = get_plot();

    string command = "plot '" + plot_output_file_name + "'";

    // 1. Transfer string -> wchar_t
    // 2. Move on to the argument of plot->cmd drawing graph
    plot->cmd(wstring(command.begin(), command.end()).c_str());

    stop_and_wait();

    delete plot;
}

bool My_Utils::is_finished(int correct_count, int size_of_inputs)
{
    if (correct_count == size_of_inputs)
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