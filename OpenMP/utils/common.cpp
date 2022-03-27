#include "common.h"
#include <string>

using namespace std;

//globals
long long int g_num_elements = 100;
unsigned int g_num_threads = 2;
std::vector<double> results(2,0);

void parseArgs(int argc, char *argv[]) {
  if(argc <= 1) {
    return;
  }

  for (int i=1; i<argc; ++i) {
    string str = argv[i];
    if (str == "-N" && argc > i+1) {
      str = argv[i+1];
      g_num_elements = stoll(str);
      i++;
    } else if (str == "-T" && argc > i+1) {
      str = argv[i+1];
      g_num_threads = stoi(str);
      i++;
    }
  }
}

void initVec(std::vector<int>& V) {
  long long idx;
  #pragma omp parallel for default(none) shared(V)
  for(idx=0; idx < V.size(); ++idx) {
    V[idx] = idx+1;
  }
}

void getRandomVec(std::vector<int>& V) {
  long long idx;
  #pragma omp parallel for default(none) shared(V)
  for(idx=0; idx < V.size(); ++idx) {
    V[idx] = rand();
  }
}

void getBinaryVec(std::vector<bool>& V) {
  long long idx;
  #pragma omp parallel for default(none) shared(V)
  for(idx=0; idx < V.size(); ++idx) {
    V[idx] = (rand()%2 == 1 ? true : false);
  }
}

void reportResults() {
  auto time_diff = (results[serial] - results[parallel])*100;
  printf("===================================================\n");
  printf("================= Execution Report ================\n");
  printf("Total number of elements : %lld\n",g_num_elements);
  printf("Total number of thread in parallel env : %d\n",g_num_threads);
  printf("Time taken for serial run   : %f\n", results[serial]);
  printf("Time taken for parallel run : %f\n", results[parallel]);
  if (time_diff > 0) {
    printf("Time saved : %f %\n",time_diff/results[serial]);
  } else {
    printf("Time lost : %f %\n",time_diff/results[serial]);
  }
  printf("===================================================\n");
}