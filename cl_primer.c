#include "cl_primer.h"

#include <stdio.h>
#include <string.h>

//TODO Write init and cleanup functions
//TODO Format kernel.cl file
//TODO Organise all files
//TODO Write Makefile
//TODO Separate main function
//TODO Test

int 		main(void)
{
	//-------------------------------------------------------------------
	// Init OpenCL structure
	//-------------------------------------------------------------------
	t_cl		*cl;

	cl = (t_cl *)malloc(sizeof(t_cl));

	//-------------------------------------------------------------------
	//Create 2 input methods
	//-------------------------------------------------------------------
	t_elems		*elems;
	int 		*res;
	int 		i;

	i = 0;
	elems = (t_elems *)malloc(sizeof(t_elems));
	elems->a = (int *)malloc(sizeof(int) * elems->NDRANGE);
	elems->b = (int *)malloc(sizeof(int) * elems->NDRANGE);
	elems->NDRANGE = 1024; //Total number of elements in the array to be processed
	elems->kernel_name = strdup("kernel.cl");
	elems->function_name = strdup("vector_add");
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
