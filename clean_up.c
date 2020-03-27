#include "cl_primer.h"

//TODO do all the structs cleanup

void 		cl_clean_up(t_cl *cl)
{
	t_cl_dev_info		*di;

	di = cl->dev_info;
	di->ret = clFlush(cl->context->command_queue);
	di->ret = clFinish(cl->context->command_queue);
	di->ret = clReleaseKernel(cl->context->kernel);
	di->ret = clReleaseProgram(cl->context->program);
	cl_clean_mem_objs(cl); //Change this function to clean your memory objects
	di->ret = clReleaseCommandQueue(cl->context->command_queue);
	di->ret = clReleaseContext(cl->context->context);
}

void 		cl_clean_mem_objs(t_cl *cl)
{
	//-------------------------------------------------------------------
	//Change this function following the below template to release all your memory objects
	//-------------------------------------------------------------------
	t_cl_items			*its;
	t_cl_dev_info		*di;

	its = cl->items;
	di = cl->dev_info;
	di->ret = clReleaseMemObject(its->a_mem_obj);
	di->ret = clReleaseMemObject(its->b_mem_obj);
	di->ret = clReleaseMemObject(its->c_mem_obj);
}