#include <cstdio>
#include <omp.h>

#define N 101202

int check_res(double * v, int n) {
  int err = 0;
  for(int i = 0; i < n; i++)
    if(v[i] != (double)i) {
      err++;
      printf("Err at %d, expected %lf, got %lf\n", i, (double)i, v[i]);
      if (err > 10)
	return err;
    }
  return err;
}

int main() {
  int devnums = 2;
  int devids[] = {0,1};
  int n = N;
  int err = 0;
  omp_memspace_handle_t managed_memory = omp_get_memory_space(devnums, devids, llvm_omp_target_shared_mem_space);

  omp_allocator_handle_t managed_allocator = omp_init_allocator(managed_memory, 0, {});

  double *a = (double *)omp_alloc(n*sizeof(double), managed_allocator);

  #pragma omp target teams distribute parallel for map(to:a)
  for(int i = 0; i < N; i++) {
    a[i] = (double)i;
  }

  err = check_res(a, n);

  omp_free(a, managed_allocator);

  if (err) return err;

  {
    double b[100];
    #pragma omp allocate(b) allocator(managed_allocator)
    double *b_p = &(b[0]);
    #pragma omp target teams distribute parallel for map(to:b_p)
    for(int i = 0; i < 100; i++) {
      b_p[i] = (double)i;
    }

    err = check_res(b, 100);
    if (err) return err;
  }
  
  // the following is stacktracing, taking it off for now
  #if 0
  omp_alloctrait_t tt[] = {{omp_atk_alignment,16}};
  double c[100];
  //#pragma omp target teams distribute parallel for uses_allocators(managed_allocator(tt)) allocate(managed_allocator: c) firstprivate(c)
  #pragma omp target teams distribute parallel for uses_allocators(managed_allocator(tt)) allocate(managed_allocator: c) firstprivate(c)
  for(int i = 0; i < 100; i++) {
    c[i] = i;
  }

  err = check_res(c, n);
  #endif

  return err;
}
