#include "cl_primer.h"

#include <stdio.h>

//TODO Write cleanup functions
//TODO Format kernel.cl file
//TODO Organise all files
//TODO Write Makefile
//TODO Separate main function
//TODO Test

int 		main(void)
{
	//-------------------------------------------------------------------
	// Init OpenCL structures
	//-------------------------------------------------------------------
	t_cl		*cl;
	t_elems		*elems;

	cl = init_opencl_structs();

	//-------------------------------------------------------------------
	// Init OpenCL structures for your data
	//
	// Change this function to suit you
	//
	// First argument - NDRange - total number of elements in the array to be processed
	// Second argument - name of your kernel file
	// Third argument - name of the vector function to be called in the kernel file
	//-------------------------------------------------------------------
	elems = init_opencl_elems(1024, "kernel.cl", "vector_add");

	//-------------------------------------------------------------------
	//Create 2 input methods
	//-------------------------------------------------------------------
	int 		*res;
	int 		i;

	i = 0;
	while (i < elems->NDRANGE)
	{
		elems->a[i] = i;
		elems->b[i] = elems->NDRANGE - i;
		i++;
	}

	//-------------------------------------------------------------------
	//Perform OpenCL calculation && write the results to *res
	//-------------------------------------------------------------------
	res = opencl_calc(cl, elems);

	//-------------------------------------------------------------------
	//Display the results on screen
	//-------------------------------------------------------------------
	i = 0;
	while (i < elems->NDRANGE)
	{
		printf("%d + %d = %d\n", elems->a[i], elems->b[i], res[i]);
		i++;
	}

	//-------------------------------------------------------------------
	//Clean up OpenCl stuff
	//
	//Go into this function, and change "cl_clean_mem_objs" to clean up your memory objects
	//-------------------------------------------------------------------
	cl_clean_up(cl);

	//-------------------------------------------------------------------
	//Clean up everything else
	//-------------------------------------------------------------------
	free(&elems->a);
	free(&elems->b);
	free(&res);
}
