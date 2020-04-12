#include "libcl.h"

void 		load_kernel_src_code(char *kernel, t_cl *cl)
{
	cl->kernel_src->fd = open(kernel, O_RDONLY);
	if (cl->kernel_src->fd <= 0)
	{
		printf(KERNEL_LOAD_ERR);
		exit(1);
	}
	cl->kernel_src->source_size = read(cl->kernel_src->fd, cl->kernel_src->source_str,\
			MAX_SOURCE_SIZE);
	close(cl->kernel_src->fd);
}

void 		create_context_coms_queue(t_cl *cl)
{
	t_cl_context		*cntx;

	cntx = cl->context;
	cntx->context = clCreateContext(NULL, 1, &cl->dev_info->device_id,\
			NULL, NULL, &cl->dev_info->ret);
	if (cl->dev_info->ret < 0)
	{
		printf(CONTEXT_ERR);
		exit(1);
	}
	cntx->command_queue = clCreateCommandQueue(cntx->context,\
			cl->dev_info->device_id, 0, &cl->dev_info->ret);
	if (cl->dev_info->ret < 0)
	{
		printf(QUEUE_ERR);
		exit(1);
	}
}

void 		create_buffs(t_cl *cl, t_elems *elems)
{
	//---------------------------------------------------------------------------------
	//Here, buffers for each given vector of the program should be declared and processed
	//Below is a template for the test code
	//Items are stored in the t_cl_items structure
	//---------------------------------------------------------------------------------
	t_cl_items			*its;
	int 				*a;
	int 				*b;
	int 				NDRANGE;
	t_test				*test;

	its = cl->items;
	a = elems->a;
	b = elems->b;
	NDRANGE = elems->NDRANGE;
	test = elems->test;
	//---------------------------------------------------------------------------------
	//Declare "CL_MEM_READ_ONLY" for the read array (i.e. things to sum together),
	// or "CL_MEM_WRITE_ONLY" for the write array (i.e. result)
	// or "CL_MEM_USE_HOST_PTR" to use host memory area as buff (i.e. if you passing a structure)
	//
	//Change "sizeof(int)" to the appropriate type
	//---------------------------------------------------------------------------------
	its->a_mem_obj = clCreateBuffer(cl->context->context, CL_MEM_READ_ONLY,\
			NDRANGE * sizeof(int), NULL, &cl->dev_info->ret);
	its->b_mem_obj = clCreateBuffer(cl->context->context, CL_MEM_READ_ONLY,\
			NDRANGE * sizeof(int), NULL, &cl->dev_info->ret);
	// Configure this to create an object which will store your result
	its->c_mem_obj = clCreateBuffer(cl->context->context, CL_MEM_WRITE_ONLY,\
			NDRANGE * sizeof(int), NULL, &cl->dev_info->ret);
	its->test_mem_obj = clCreateBuffer(cl->context->context, CL_MEM_USE_HOST_PTR, sizeof(t_test), test, &cl->dev_info->ret);
	cpy_to_buffs(cl, a, b, NDRANGE);
	if (cl->dev_info->ret < 0)
	{
		printf(BUFF_CREAT_ERR);
		exit(1);
	}
	set_kernel_args(cl);
}

void 		cpy_to_buffs(t_cl *cl, int *a, int *b, int NDRANGE)
{
	//-------------------------------------------------------------------
	//Copy the lists A and B to their respective memory buffers as per template below
	//
	//Change "cl->items->a_mem_obj" to the appropriate buffer
	//Change "sizeof(int) to the appropriate type
	//Change "a" to appropriate pointer
	cl->dev_info->ret = clEnqueueWriteBuffer(cl->context->command_queue,\
			cl->items->a_mem_obj, CL_TRUE, 0, NDRANGE * sizeof(int), a,\
			0, NULL, NULL);
	cl->dev_info->ret = clEnqueueWriteBuffer(cl->context->command_queue,\
			cl->items->b_mem_obj, CL_TRUE, 0, NDRANGE * sizeof(int), b,\
			0, NULL, NULL);
	if (cl->dev_info->ret < 0)
	{
		printf(BUFF_CPY_ERR);
		exit(1);
	}
}