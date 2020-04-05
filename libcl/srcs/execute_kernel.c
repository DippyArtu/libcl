#include "libcl.h"

void 		exec_kernel(t_cl *cl, int NDRANGE)
{
	//-------------------------------------------------------------------
	//Execute the OpenCL kernel on the list
	//-------------------------------------------------------------------
	t_cl_context		*cntx;

	cntx = cl->context;
	cntx->ndrange = NDRANGE;
	cntx->work_group = 64; //You can change this to a desired size of a work group
	cl->dev_info->ret = clEnqueueNDRangeKernel(cntx->command_queue,\
			cntx->kernel, 1, NULL, &cntx->ndrange, &cntx->work_group,\
			0, NULL, NULL);
	if (cl->dev_info->ret < 0)
	{
		printf(EXEC_ERR);
		exit(1);
	}
}

int 		*read_buff(t_cl *cl, int NDRANGE)
{
	int 				*res;

	res = (int *)malloc(sizeof(int) * NDRANGE); //Change type to the desired type
	cl->dev_info->ret = clEnqueueReadBuffer(cl->context->command_queue,\
			cl->items->c_mem_obj, //Change this to the actual object which will host the result of a calculation
			CL_TRUE, 0,NDRANGE * sizeof(int), //Change type to the desired type
			res, 0, NULL, NULL);
	if (cl->dev_info->ret < 0)
	{
		printf(BUFF_READ_ERR);
		exit(1);
	}
	return (res);
}