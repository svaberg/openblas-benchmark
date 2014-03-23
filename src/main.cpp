#include <iostream>
#include <iomanip>
#include <fstream>
#include <sys/time.h>
#include <algorithm>
#include <cfloat>

#include <armadillo>

using namespace std;

struct result_t
{
    unsigned int size;
    double min_time, avg_time, max_time;
};

double time_diff(timeval t1, timeval t2)
{
    double t;
    t = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    t += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

    return t;
}

void dump(const string &file, const vector<result_t> &results)
{
    const unsigned width = 11;

    ofstream arrayData(file.c_str());

    arrayData << setw(width) << "Size";
    arrayData << setw(width) << "Average";
    arrayData << setw(width) << "Minimum";
    arrayData << setw(width) << "Maximum" << endl;

    arrayData << setw(width) << "";
    arrayData << setw(width) << "[ms]";
    arrayData << setw(width) << "[ms]";
    arrayData << setw(width) << "[ms]" << endl;

    for(int k = 0; k < results.size(); k++)
    {
        arrayData << setw(width) << results[k].size;
        arrayData << setw(width) << results[k].avg_time;
        arrayData << setw(width) << results[k].min_time;
        arrayData << setw(width) << results[k].max_time << endl;
    }
}

result_t time(unsigned size, unsigned iterations)
{
    timeval t0, t1;

    result_t result;
    result.size = size;
    result.min_time = DBL_MAX;
    result.avg_time = 0;
    result.max_time = 0;

    for(int i=0; i < iterations; i++) 
    {

        // Set up stuff
        arma::mat A(size, size, arma::fill::randn);
        arma::mat B(size, size, arma::fill::randn);
        arma::mat C(size, size);

        // measure execution time
        gettimeofday(&t0, NULL);
	C = A * B;
        gettimeofday(&t1, NULL);

	double time = time_diff(t0, t1);

        result.avg_time += time / iterations;
        if (time > result.max_time)
        {
             result.max_time = time;
        }
        if (time < result.min_time)
        {
             result.min_time = time;
        }
    }

    return result;
}

int main(int argc, char** argv)
{
    //openblas_get_number_of_threads();
    string file;
    {
        const char *openblas_env_variable = "OPENBLAS_NUM_THREADS";
        char *openblas_threads = getenv(openblas_env_variable);
        
        if (openblas_threads != NULL)
        {
            cout << openblas_env_variable << "=" << openblas_threads << endl;
        }

        std::ostringstream oss;
        oss << "results/results_" << openblas_threads << ".data";
        file = oss.str();
    }

    vector<unsigned> sizes;
    vector<unsigned> iterations;

    cout << "Sizes: ";
    unsigned min_size = 32;
    unsigned max_size = 512;
    double step = pow(2, 1.0/3.0);
    for (double i_size = min_size; i_size <= max_size; i_size *= step)
    {
        unsigned iteration = 6;

        sizes.push_back(i_size);
        iterations.push_back(iteration);

        cout << i_size << " " ;
    }
    cout << endl;

    vector<result_t> results;

    for(unsigned i=0; i < sizes.size(); i++)
    {
        result_t result = time(sizes[i], iterations[i]);
        results.push_back(result);
  
        cout << "Size:" << setw(6) << result.size << " Average time [ms]: " << setw(9) << result.avg_time << endl; 
    }

  dump(file, results);
    return 0;
}
