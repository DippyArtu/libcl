#ifndef _CL_PRIMER_H
# define CL_PRIMER_H

# ifndef _STDLIB_H_
#  include <stdlib.h>
# endif

# include "cl_structs.h"

# define MAX_SOURCE_SIZE (0x100000)

int 		*opencl_calc(t_cl *cl, t_elems *elems);
void 		init_opencl_structs(void);
void 		load_kernel_src_code(char *kernel, t_cl *cl);
void 		get_cl_info(t_cl *cl);
void 		create_context_coms_queue(t_cl *cl);
void 		create_buffs(t_cl *cl, int *a, int *b, int NDRANGE)
void 		cpy_to_buffs(t_cl *cl, int *a, int *b, int LIST_SIZE);
void 		prep_kernel(t_cl *cl, char *kernel_name);
void 		set_kernel_args(t_cl *cl);
void 		exec_kernel(t_cl *cl);
int 		*read_buff(t_cl *cl, int NDRANGE);
void 		cl_clean_up(t_cl *cl);
void 		cl_clean_mem_objs(t_cl *cl);


#endif
