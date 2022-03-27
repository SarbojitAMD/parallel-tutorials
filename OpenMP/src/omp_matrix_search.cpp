#include "../utils/common.h"
#include <math.h>

using namespace std;

/* Goal:
 * As a CPP dev one must have written program to search an element in a 
 * unsorted 2D matrix the data set. With this simple algorithm 
 * I am trying to highlight some key OpenMP features :
 *   1> Minimal change required in the serial program to enable parallelism via OpenMP
 *   2> OpenMP Key Feature to watch in this program 'collapse'
 *
 *  Performance gain seen on System (8core CPU + Windows10) is ~70%
 */

bool find_serial(vector<vector<int>>& Mat, int val) {
  long row = Mat.size();
  long col = Mat[0].size();
  long i,j;
  auto start = omp_get_wtime();
  for(i=0; i<row; ++i) {
    for(j=0; j<col; j++) {
      if (Mat[i][j] == val) {
        return true;
      }
    }
  }
  auto end = omp_get_wtime();
  results[serial] = end-start;
  return false;
}

bool find_parallel(vector<vector<int>>& Mat, int val) {
  long row = Mat.size();
  long col = Mat[0].size();
  long i,j;
  bool found=false;
  auto start = omp_get_wtime();
  #pragma omp parallel for collapse(2) default(none) reduction(|:found) firstprivate(row,col,val) shared(Mat) private(j)
  for(i=0; i<row; ++i) {
    for(j=0; j<col; j++) {
      if (Mat[i][j] == val) {
        found = true;
      }
    }
  }
  auto end = omp_get_wtime();
  results[parallel] = end-start;
  return found;
}

int main(int argc, char* argv[]) {
  long row=0,col=0;
  parseArgs(argc, argv);
  row = col = sqrt(g_num_elements);
  vector<vector<int>> Mat(row,vector<int>(col,0));
  find_parallel(Mat, 10);
  find_serial(Mat,10);
  reportResults();
  return 0;
}