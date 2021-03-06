#include "libcl.h"

void 		print_log(t_cl *cl)
{
	char 				*prog_log;
	size_t 				log_size;

	printf(PROGRAM_BUILD_ERR);
	clGetProgramBuildInfo(cl->context->program, cl->dev_info->device_id, \
			CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	prog_log = (char *)malloc(sizeof(char) * (log_size + 1));
	prog_log[log_size] = '\0';
	clGetProgramBuildInfo(cl->context->program, cl->dev_info->device_id, \
			CL_PROGRAM_BUILD_LOG, log_size + 1, prog_log, NULL);
	printf("%s\n", prog_log);
	free(prog_log);
	exit(1);
}

void 		create_program(t_cl *cl)
{
	t_cl_context		*cntx;

	cntx = cl->context;
	cntx->program = clCreateProgramWithSource(cntx->context, 1,\
			(const char **)&cl->kernel_src->source_str,\
			(const size_t *)&cl->kernel_src->source_size,\
			&cl->dev_info->ret);
	if (cl->dev_info->ret < 0)
	{
		printf(PROGRAM_ERR);
		exit(1);
	}
}

void 		build_program(t_cl *cl, char *include)
{
	t_cl_context		*cntx;
	cl_int 				err;

	cntx = cl->context;
	err = cl->dev_info->ret = clBuildProgram(cntx->program, 1,\
			&cl->dev_info->device_id, include, NULL, NULL);
	if (cl->dev_info->ret < 0)
		print_log(cl);
}

void 		prep_kernel(t_cl *cl, char *kernel_ft, char *include)
{
	t_cl_context		*cntx;

	cntx = cl->context;
	create_program(cl); //Create a program from the kernel source
	build_program(cl, include); //Build the program
	//Create the OpenCL kernel
	cntx->kernel = clCreateKernel(cntx->program,\
			kernel_ft, &cl->dev_info->ret);
	if (cl->dev_info->ret < 0)
	{
		printf("%i\n", cl->dev_info->ret);
		printf(KERNEL_CREAT_ERR);
		exit(1);
	}
}

void 		set_kernel_args(t_cl *cl)
{
	//Set arguments of the kernel according to the template below
	//Change "cl->items->a_mem_obj" to the actual memory object
	cl->dev_info->ret = clSetKernelArg(cl->context->kernel, 0, sizeof(cl_mem),\
			(void *)&cl->items->a_mem_obj);
	cl->dev_info->ret = clSetKernelArg(cl->context->kernel, 1, sizeof(cl_mem),\
			(void *)&cl->items->b_mem_obj);
	cl->dev_info->ret = clSetKernelArg(cl->context->kernel, 2, sizeof(cl_mem),\
			(void *)&cl->items->c_mem_obj);
	cl->dev_info->ret = clSetKernelArg(cl->context->kernel, 3, sizeof(cl_mem),\
			(void *)&cl->items->test_mem_obj);
	if (cl->dev_info->ret < 0)
	{
		printf(ARG_ERR);
		exit(1);
	}
}