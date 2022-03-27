
#include "../utils/common.h"

/* Goal:
 * This program highlights some key points :
 *   1> How easy to enable parallelism in a program using OpenMP
 *   2> OpenMP's fork-join model
 *
 * omp parallel compiler directive creates threads and run the structure block in parallel
 * Because structure block runs parallel output will be different every time test is run
 */
int main(int argc, char *argv[]) {
  parseArgs(argc,argv);
  #pragma omp parallel
  {
  printf("Hello");
  printf(" World");
  printf("\n");
  }
  return 0;
}