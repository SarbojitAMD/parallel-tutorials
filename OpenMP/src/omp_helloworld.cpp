#include <omp.h>
#include <iostream>
#include "../utils/common.h"

/*
 * omp parallel compiler directive creates threads and run the structure block in parallel
 * Because structure block runs parallel output will be different every time
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