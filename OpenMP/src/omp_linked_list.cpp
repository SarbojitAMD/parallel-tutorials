#include "../utils/common.h"
#include <ctime>

using namespace std;

/* Goal:
 * Explore OpenMP task parallelism in linked list traversal.
 * By the program I wanted to show task parallelism has overhead hence
 * it is useful only when task is a time taking task else it impacts 
 * the performance
 */

typedef struct node{
  int data_;
  node* next_;
}node;

node* head_ll = nullptr;

void create_ll(int num) {
  node* temp = nullptr;
  node* curr = nullptr;
  while(num--) {
    temp = new node;
    temp->data_ = rand();
    temp->next_ = nullptr;
    if(curr) {
      curr->next_ = temp;
    } else {
      head_ll = temp;
    }
    curr=temp;
  }
}

long count_even_ele_serial(node* head) {
  node* curr = head;
  long count = 0;
  auto start = omp_get_wtime();
  while(curr != nullptr) {
    if (curr->data_ % 2 == 0) {
      count++;
    }
    curr = curr->next_;
  }
  auto end = omp_get_wtime();
  results[serial] = end-start;
  return count;
}

long count_even_ele_parallel(node* head) {
  node* curr = head;
  long count = 0;
  auto start = omp_get_wtime();
  #pragma omp parallel default(none) shared(count) firstprivate(curr)
  {
    #pragma omp single
    {
      while(curr) {
        #pragma omp task firstprivate(curr) shared(count)
        {
          if (curr->data_%2 == 0) {
            count++;
          }
        }
        curr = curr->next_;
      }
    }
  }
  auto end = omp_get_wtime();
  results[parallel] = end-start;
  return count;
}

int main(int argc, char* argv[]) {
  srand(time(0));
  parseArgs(argc, argv);
  create_ll(g_num_elements);

  cout<<count_even_ele_serial(head_ll)<<endl;
  cout<<count_even_ele_parallel(head_ll)<<endl;

  reportResults();
  return 0;
}