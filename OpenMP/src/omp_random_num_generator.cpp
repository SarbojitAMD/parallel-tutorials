#include "../utils/common.h"
#include <vector>
#include <ctime>

/*
 * Goal here is to show one of the very common use case where
 * huge array needs to be filled with random integer numbers.
 * 
 * Performance gain seen on System (8core CPU + Windows10) is ~80%
 */

void generate_N_serial(std::vector<int>& V) {
  auto start = omp_get_wtime();
  for(auto i=0; i<V.size(); ++i) {
    V[i] = rand();
  }
  auto end = omp_get_wtime();
  results[serial] = end-start;
}

void generate_N_parallel(std::vector<int>& V) {
  size_t i;
  omp_set_num_threads(g_num_threads);
  auto start = omp_get_wtime();
  #pragma omp parallel for default(none) shared(V)
  for(i=0; i<V.size(); ++i) {
    V[i] = rand();
  }
  auto end = omp_get_wtime();
  results[parallel] = end-start;
}

int main(int argc, char* argv[]) {
  srand(time(0));
  parseArgs(argc, argv);
  std::vector<int> V(g_num_elements,0);

  generate_N_parallel(V);
  generate_N_serial(V);

  reportResults();
  return 0;
}