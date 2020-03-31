__kernel void		vector_add(__global const int *a, __global const int *b, __global int *c)
{
	//Get the index of the current element to be processed
	int 	i;

	i = get_global_id(0);
	//Add elements together
	c[i] = a[i] +  b[i];
}