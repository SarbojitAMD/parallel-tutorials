#include "../utils/common.h"

using namespace std;

long long count_ones_serial(vector<bool>& V) {
  long long count=0;
  auto start = omp_get_wtime();
  for (long long i=0; i<V.size(); ++i) {
    count += static_cast<int>(V[i]);
  }
  auto end = omp_get_wtime();
  results[serial] = end-start;
  return count;
}

long long count_ones_parallel(vector<bool>& V) {
  long long i;
  long long count=0;
  auto start = omp_get_wtime();
  #pragma omp parallel for default(none) reduction(+:count) shared(V)
  for (i=0; i<V.size(); ++i) {
    count += static_cast<int>(V[i]);
  }
  auto end = omp_get_wtime();
  results[parallel] = end-start;
  return count;
}

int main(int argc, char* argv[]) {
  parseArgs(argc, argv);

  vector<bool> V(g_num_elements, false);
  getBinaryVec(V);

  cout<<count_ones_parallel(V)<<endl;
  cout<<count_ones_serial(V)<<endl;
  reportResults();
}