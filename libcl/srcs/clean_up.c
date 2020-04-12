#include "libcl.h"

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

void 		cl_clean_structs(t_cl *cl, t_elems *elems)
{
	free(cl->kernel_src->source_str);
	cl->kernel_src->source_str = NULL;
	free(cl->kernel_src);
	cl->kernel_src = NULL;
	free(cl->dev_info);
	cl->dev_info = NULL;
	free(cl->context);
	cl->context = NULL;

	//-------------------------------------------------------------------
	//Clean up your structures below

	free(cl->items);
	cl->items = NULL;
	free(elems->a);
	elems->a = NULL;
	free(elems->b);
	elems->b = NULL;
	free(elems);
	elems = NULL;
	//-------------------------------------------------------------------

	free(cl);
	cl = NULL;
}

void 		cl_clean_up_all(t_cl *cl)
{
	t_cl_dev_info		*di;

	di = cl->dev_info;
	di->ret = clFlush(cl->context->command_queue);
	di->ret = clFinish(cl->context->command_queue);
	di->ret = clReleaseKernel(cl->context->kernel);
	di->ret = clReleaseProgram(cl->context->program);
	di->ret = clReleaseCommandQueue(cl->context->command_queue);
	di->ret = clReleaseContext(cl->context->context);
}

void 		cl_clean_up(t_cl *cl)
{
	//-------------------------------------------------------------------
	// If you plan on reusing your kernel, you shouldn't be getting rid of
	// your kernel, program, queue and context.
	// You should, however, clean up your memory objects (unless you need them,
	// of course) and anything else that you don't plan on reusing.
	//
	//To reuse your kernel with updated buffers, simply create new buffers via
	// create_buffs(); and call exec_kernel();
	//
	//You can also pass a memory buffer from one kernel to the other, in doing so,
	//instead of deleting your buffer, simply set it as an argument of a second kernel.
	//
	//Keep in mind, that for every new kernel, you have to create new program and kernel.
	//You don't have to use new queue or context, so simply add new objects for your second
	//kernel and program into the t_cl_kernel_src and t_cl_context structures and you are
	//good to go.
	//-------------------------------------------------------------------

	cl_clean_mem_objs(cl); //Change this function to clean your memory objects
}