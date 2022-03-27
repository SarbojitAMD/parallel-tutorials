#include "../utils/common.h"
bool find_sequential(std::vector<int>& V, int val) {
  long long idx;
  bool found = false;
  auto start = omp_get_wtime();
  for(idx =0; idx < V.size(); idx++){
    if (V[idx] == val) {
      found = true;
      break;
    }
  }
  auto end = omp_get_wtime();
  results[serial] = end-start;
  return found;
}

bool find_parallel(std::vector<int>& V, int val) {
  long long idx;
  bool found = false;
  auto start = omp_get_wtime();
  #pragma omp parallel for default(none) shared(V) firstprivate(val) reduction(|:found)
  for(idx =0; idx < V.size(); idx++) {
    if (V[idx] == val) {
      found = true;
    }
  }
  auto end = omp_get_wtime();
  results[parallel] = end-start;
  return found;
}

int main(int argc, char* argv[]) {
  parseArgs(argc, argv);

  std::vector<int> V(g_num_elements,0);
  initVec(V);
  int findMe = g_num_elements+1; 

  find_sequential(V, findMe);
  find_parallel(V,findMe);

  reportResults();
  return 0;
}