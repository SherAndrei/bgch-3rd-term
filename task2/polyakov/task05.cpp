#include "data.h"
#include "array.h"



void task5(data * a, int n);
void task5(data * a, int n) {

  int i, k, min;

  for (i=0; i<n; ++i) {
    min=i;
    for (k=i+1; k<n; ++k) {
      if (a[k]<a[min]) min=k;
    }
    if (i<min) a[i].swap(a[min]);
  }
}


int data::p = 0;

int main(int argc, char * argv[]) {
  int n, p, s;
  int ret, task;
  char * filename = nullptr;
  data * a = nullptr;
  double t;

  if (argc==4) {
    if (!(sscanf(argv[1], "%d", &n)==1 && sscanf(argv[2], "%d", &p)==1 && sscanf(argv[3], "%d", &s)==1 && s>=1 && s<=4 && n>0 && p>0)) { 
      printf("Usage: n p (s) filename\n");
      return ERROR;
    }
  }
  else if (argc==5) {
    if (!(sscanf(argv[1], "%d", &n)==1 && sscanf(argv[2], "%d", &p)==1 && sscanf(argv[3], "%d", &s)==1 && s==0 && n>0 && p>0)) { 
      printf("Usage: n p (s) filename\n");
      return ERROR;
    }
    filename = argv[5];
  }
  else {
    printf("Usage: n p (s) filename\n");
    return ERROR;
  }

  data::set_p(p);

 a = new data[n];
  if (!a) {
    printf("Not enough memory!\n");
    return ERROR_MEMORY;
  }
  if (filename) {
    ret = initialize_data_array1(n, filename, a);
      if (ret!=SUCCESS) {
        switch(ret) {
          case ERROR_OPEN:
            printf("Cannot open %s\n", filename);
            break;
          case ERROR_READ:
            printf("Cannot read %s\n", filename);
            break;
          default:
            printf("Unknown error %d\n", ret);
        }
        delete[] a;
        return ERROR;
    }
  }
  else initialize_data_array2(n, s, a);
  
  printf("Array:\n");
  print_array(n, a);
  
  t = clock();
  task5(a, n);
  t = (clock()-t)/CLOCKS_PER_SEC; 
  printf("New array:\n");
  print_array(n, a);
 
  task=5;
  printf("%s : Task = %d Diff = %d Elapsed = %.2f\n",
        argv[0], task, diff(n, a), t);


  delete[] a;
  return 0;
}
