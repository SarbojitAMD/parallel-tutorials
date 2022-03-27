#include <iostream>
#include <vector>
#include <omp.h>

void parseArgs(int argc, char *argv[]);
void initVec(std::vector<int>& V);
void getRandomVec(std::vector<int>& V);
void getBinaryVec(std::vector<bool>& V);
void reportResults();

extern long long int g_num_elements;
extern unsigned int g_num_threads;
extern std::vector<double> results;

enum execution {
  serial,
  parallel
};

