# parallel_tutorials

<p align="left">This is a hobby learning repository where I am trying to write parallel implementation of some of the commonly used simple algorithms. I will be writing algorithms in all known parallel methods such as OpenMP, MPI, TBB etc </p>


### OpenMP
**This folder contains algorithms written in OpenMP which I have created while learning OpenMP.**

<p align="left">I have followed Tim Mattson's Introduction to OpenMP video playlist on youtube. It is definitely the one which every OpenMP learner should reffer.</p>

### Details
<p align="left">I am learning OpenMP as part of my hobby learning. In the process of learning I am trying to use it to some of the common yet simple case where I think OpenMP can be beneficial. It is more of my experiements with OpenMP hence it will not be a comprehensive tutorial guide.</p>

**Build Steps**

**build command :**
g++ -fopenmp src/omp_omp_random_num_generator.cpp utils/common.cpp -o bin/omp_random_num_generator

**run command:**
./bin/omp_random_num_generator -N 100000000 -T 8

[Note: -N : Number of elements , -T : Number of threads]

<p align="left">common.h and common.cpp are two files which has common implements. For example commandline parser, routine to generate reports. I have used them in other programs hence during compilation of source I have included them. I have used GCC for compilation and collecting results.</p>


## Repositories
|   File name  |                 Description                                                                                                                                   |
|----------|---------------------------------------------------------------------------------------------------------------------------------------------------------------|
|omp_helloworld.cpp|Printing Hello World using OpenMP                                                                                                                      |
|omp_random_num_generator.cpp|Simple random number generator                                                                                                                      |
|omp_sequential_search.cpp|Searching an integer value in an unsorted list                                                                                                                      |
|omp_count_frequency.cpp|Counts how many times one has occured in an random list of 0/1                                                                                                                      |
|omp_linked_list.cpp|Travers the linked list to count even elements using OpenMP task                                                                                                                      |
|omp_standard_deviation.cpp|Calculate SD of a given set of random integers                                                                                                                      |
|omp_matrix_search.cpp|Search an element in 2D matrix                                                                                                                      |