#ifndef _CL_STRUCTS_H
# define _CL_STRUCTS_H

# include <OpenCL/opencl.h>
# include <opencl-c-base.h>

//----------------------------------------------------------------
// Here goes structures containing objects for OpenCL to work with
// i.e. items for your actual function manipulations

typedef struct 		s_elements
{
	int 		*a;  //Variable a
	int 		*b;  //Variable b
	int 		NDRANGE; //Total number of items (calculations to perform)
	char 		*kernel_name; //Name of the vector code file (i.e. kernel.cl)
	char 		*function_name; //Name of the function to perform in the vector (i.e. vector_add)
}					t_elems;

typedef struct		s_cl_items
{
	cl_mem 				a_mem_obj;
	cl_mem 				b_mem_obj;
	cl_mem 				c_mem_obj;
}					t_cl_items;

//----------------------------------------------------------------

typedef struct 		s_cl_kernel_src
{
	int 				fd;
	char				*source_str;
	size_t				source_size;
}					t_cl_kernel_src;

typedef struct 		s_cl_dev_info
{
	cl_platform_id		platform_id;
	cl_device_id 		device_id;
	cl_uint 			num_devices;
	cl_uint 			num_platforms;
	cl_int 				ret;
}					t_cl_dev_info;

typedef  struct		s_cl_context
{
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;
	size_t 				ndrange;
	size_t 				work_group;
}					t_cl_context;

typedef struct		s_cl
{
	t_cl_context		*context;
	t_cl_dev_info		*dev_info;
	t_cl_kernel_src		*kernel_src;
	//Include links to the working structures below
	t_cl_items			*items;
}					t_cl;

#endif
