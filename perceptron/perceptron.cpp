#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#undef RANDOM
#define RANDOM() (((double) rand() / 100.0) - 160.0)    // -160.0 ~ 167.67

using namespace std;

vector<vector<int>> inputs;
vector<double> weights;

int get_dimension();
void generate_inputs(int depth, int dimension, int &sequence, vector<int> &input);
void generate_weights(int dimension);
double inner_product(int sequence, int dimension);
void print_case(int sequence, int dimension, int answer, double output);
bool print_result(double output, int answer);
bool print_summary(int count_correct, int dimension);
void generate_new_weights(int dimension);

int main(void)
{
    // Get dimension from user.
    int dimension = get_dimension();

    // Generate (2^dimension) inputs
    // Each input's length will be (dimension + 1).
    vector<int> input(dimension);
    int sequence = 0;

    inputs.resize(1 << dimension);

    generate_inputs(0, dimension, sequence, input);

    // Generate (dimension + 1) weights
    generate_weights(dimension);

    // Let's go
    while(true)
    {
        long long count_correct = 0;

        // Test all inputs
        for(long long i = 0; i < 1 << dimension; i++)
        {
            double output = inner_product(i, dimension);

            // AND gate
            bool answer = (i == (1 << dimension) - 1) ? 1 : 0;

            print_case(i, dimension, answer, output);

            bool result = print_result(output, answer);

            if(result) count_correct++;
        }

        bool finished = print_summary(count_correct, dimension);

        if(finished) break;

        // Try again...
        generate_new_weights(dimension);
    }

    return 0;
}


int get_dimension()
{
    int dimension;

    cout << "Enter the dimension: ";
    cin >> dimension;
    cout << "\n\n";

    return dimension;
}

void generate_inputs(int depth, int dimension, int &sequence, vector<int> &input)
{
    if(depth == dimension)
    {
        inputs[sequence].push_back(1);

        for(int i = 0; i < dimension; i++)
            inputs[sequence].push_back(input[i]);

        sequence++;

        return;
    }

    input[depth] = 0;
    generate_inputs(depth + 1, dimension, sequence, input);

    input[depth] = 1;
    generate_inputs(depth + 1, dimension, sequence, input);
}

void generate_weights(int dimension)
{
    srand(time(NULL));

    for(int i = 0; i <= dimension; i++)
        weights.push_back(RANDOM());
}

double inner_product(int sequence, int dimension)
{
    double sum = 0LL;

    for(int i = 0; i <= dimension; i++)
        sum += inputs[sequence][i] * weights[i];

    return sum;
}

void print_case(int sequence, int dimension, int answer, double output)
{
    cout << "Case " << sequence + 1 << ": ";

    for(long long i = 0; i <= dimension; i++)
        cout << inputs[sequence][i];

    cout << "\n\tAnswer: " << answer;

    cout << "\n\tNet   : " << output;

    cout << "\n\tResult: ";
}

bool print_result(double output, int answer)
{
    if((output > 0 && answer) || (output <= 0 && !answer))
    {
        cout << "CORRECT!!\n\n";

        return true;
    }

    cout << "OH MY GOD\n\n";

    return false;
}

bool print_summary(int count_correct, int dimension)
{
    cout << "\nNumber of Correct Cases: " << count_correct << " (Expected: " << (1 << dimension) << ")\n";

    if(count_correct == 1 << dimension)
    {
        cout << "\n\nFinally Finished :)\n\n\n";

        return true;
    }

    cout << "\n\nTry Again...\n\n\n";

    return false;
}

void generate_new_weights(int dimension)
{
    cout << "Enter your own weights:\n";

    for(int i = 0; i <= dimension; i++)
    {
        cout << "\tWeight " << i << ": ";

        cin >> weights[i];
    }
    
    cout << "\n\n";
}