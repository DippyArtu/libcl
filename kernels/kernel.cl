#include "kernel_structs.h"

__kernel void		vector_add(__global const int *a, __global const int *b, __global int *c, __constant t_test *test)
{
//Get the index of the current element to be processed
int 	i;

i = get_global_id(0);
//Add elements together
c[i] = a[i] + b[i] + test->val1 + test->val2;
}