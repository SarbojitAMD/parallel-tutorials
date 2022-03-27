#include "../utils/common.h"
#include <math.h>

auto SD_serial(std::vector<int>& Nums) {
  long long sum=0;
  auto start = omp_get_wtime();
  for(auto num : Nums) {
    sum += num;
  }
  auto mean = sum/Nums.size();
  sum = 0;
  for(auto num : Nums) {
    sum += pow((num-mean),2);
  }
  auto sd = sqrt(sum/Nums.size());
  auto end = omp_get_wtime();
  results[serial]=end-start;
  return sd;
}

auto SD_parallel(std::vector<int>& V) {
  long long sum=0;
  auto start = omp_get_wtime();
  long long idx;
  const long long size = V.size();
  #pragma omp parallel for default(none) reduction(+:sum) shared(V) firstprivate(size)
  for(idx=0; idx < size; ++idx) {
    sum += V[idx];
  }
  auto mean = sum/size;
  sum = 0;
  #pragma omp parallel for default(none) reduction(+:sum) shared(V) firstprivate(size, mean)
  for(idx=0; idx < size; ++idx) {
    sum += pow((V[idx]-mean),2);
  }
  auto sd = sqrt(sum/size);
  auto end = omp_get_wtime();
  results[parallel]=end-start;
  return sd;
}

int main(int argc, char* argv[]) {
  parseArgs(argc, argv);
  std::vector<int> V(g_num_elements,0);
  initVec(V);
//  getRandomVec(V);

  std::cout<<SD_parallel(V)<<std::endl;
  std::cout<<SD_serial(V)<<std::endl;
  reportResults();
  return 0;
}