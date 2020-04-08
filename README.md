
  
    
# Libcl 
### This a tiny OpenCL library/template to make starting and working with OpenCL easier.     

 **Only MacOS supported natively - Windows\Linux users will have to build from sources and configure OpenCL includes!**
 
 This repo also contains test *main.c* the project file, *kernel* and *Makefile* to compile the project with.      
      
**You should educate yourself closely with the in-code comments as well as the code.**   
## Changelog  (latest marked in bold)
- **Now you have an option to flush only the kernel and program, saving the context and all other service info for repeated use in your program by invoking `cl_clean_up(t_cl *cl)` (caution, not fully tested yet!) P.S. allocations inside elements structure aren't freed**
- Memory leaks are solved (you should still check tho, just in case)  
- Now you can learn how to pass a user-defined structure into the kernel  
- Error handling implemetned  
- Now you can create a header for the kernel file and include it into the program build  
    
## Tiny terminology    
    
 - **OpenCL (Open Computing Language)** - framework for a parralel execution of programs on different compute devices (CPUs, GPUs)    
 - **Kernel (vector)** - A function which will be sent and executed on a compute device.    
   - These files have a `.cl` extension.    
 - **NDRange** - total size of a *compute grid* - the total amount of calculations to be performed.    
 - **Work Group** - a subset of the *NDRange* which divides total workload into equal groups.    
    
      
## **Test project**    
 Test project will perform 1024 additions `(0 + 1024, 1 + 1023, ...., 1023 + 1)` on OpenCL and print the results.    
    
## **How to use**    
    
- Library itself is withing the **libcl** folder.    
 - Compile the project using **Makefile** in the root of the repo with `make`.    
 - This library operates using structures, which contain all the necessary data, including links to the input and output parameters, the name of a kernel file, as well as the NDRange value.     
   - Your structures should be placed inside the **cl_user_structs.h** file and initialized properly.    
 - **kernel.cl** is a file containing instructions to be executed in on the OpenCL device.     
   - Those should be placed in the **kernels** folder at the root of the project.    
     
 #### For a quick start using pre-configured functions and structures:    
- Call `init_opencl_structs` to initialize all the service data.     
   - This function will return a pointer to your `t_cl` struct.    
 - Call `init_opencl_elems` to initialize a structure for your data.     
   - This function will accept the *NDRange*, *name of the kernel file* and the *name of the function to be processed within the kernel file* as it's arguments and return a pointer to a `t_elems` struct.    
 - Create input methods for the data.    
 - Call `opencl_calc` function to perform the OpenCL calculation.     
   - This function will accept a *pointer to your `t_cl` struct* and a *pointer to your `t_elems` struct* as it's arguments and will return a pointer to a memory area, containing the result of a calculation.    
 - Use the result.    
 - Call `cl_clean_up` to clean up all the service data.    
   - This function accepts a *pointer to your `t_cl` struct*.    
 - Call `cl_clean_structs` to clean up structure containing your data.    
   - This function accepts a pointer to your `t_elems` struct*.    
    
**Read the in-code comments and alter the functions/headers  according to the template to fit your needs!**    
 ## Function descriptions    
 **Notes:**     
 - *Fresh* means freshly allocated with `malloc`    
 - *Cleans up* means *releases, flushes, finishes* or *frees* given areas    
     
|Declaration         |Description                |Return                       |
 |----------------|-------------------------------|-----------------------------|
  |`t_cl    *init_opencl_structs(void);`| Initializes service structures|Pointer to fresh `t_cl` struct  | |`void    init_user_cl_structs(t_cl *cl);`|Initializes structures for user memory objects| None| |`t_elems *init_opencl_elems(int NDRange, char *kernel_name, char *function_name);`|Initializes structures for user data | Pointer to fresh `t_elems` struct    
|`int     *opencl_calc(t_cl *cl, t_elems *elems);`|Performs an OpenCL calculation|Pointer to a memory area containing results fo the calculation    
|`void    load_kernel_src_code(char *kernel_name, t_cl *cl);`|Loads kernel source code into the *cl structure* | None    
|`void get_cl_info(t_cl *cl);`|Queries available OpenCL platforms & devices|None    
|`void create_context_coms_queue(t_cl *cl);`|Creates an OpenCl context & command queue|None    
|`void create_buffs(t_cl *cl, int *a, int *b, int NDRange);`|Creates memory buffers on the device for each input vector (a & b)|None    
|`void cpy_to_buffs(t_cl *cl, int *a, int *b, int NDRange);`|Copies lists A and B to their respective memory buffers|None    
|`void prep_kernel(t_cl *cl, char *kernel_name);`|Creates a program from the kernel source, builds the program & creates OpenCL kernel| None    
|`void set_kernel_args(t_cl *cl);`|Sets kernel arguments|None    
|`void exec_kernel(t_cl *cl, int NDRange);`|Executes OpenCL kernel on the given list|None    
|`int *read_buff(t_cl *cl, int NDRange);`|Allocates memory for the local variable *res* containing results of a calculation and reads the memory buffer *C* on the device to the local variable *res*|Pointer to the memory area containing results of a calculation 
|`void cl_clean_up(t_cl *cl);`|Releases kernel, program and assosiated memory objects. Device, platform, command queue and context are saved for reuse|None   
|`void cl_clean_up_all(t_cl *cl);`|Cleans up all OpenCL service data _(This function should not be used after `cl_clean_up()`, as this will most likely cause a sig fault._|None    
|`void cl_clean_mem_objs(t_cl *cl);`|Cleans up OpenCL memory areas|None    
|`void cl_clean_structs(t_cl *cl, t_elems *elems);`|Cleans up structures|None    
    
## Learning resources    
    
- [Dr. Dobb's](https://www.drdobbs.com/parallel/a-gentle-introduction-to-opencl/231002854?pgno=3) introduction to OpenCL    
 - [Jülich Forschungszentrum](https://www.fz-juelich.de/SharedDocs/Downloads/IAS/JSC/EN/slides/opencl/opencl-03-basics.pdf?__blob=publicationFile) lecture slides on OpenCL basics    
 - [Apple Developer](https://developer.apple.com/library/archive/documentation/Performance/Conceptual/OpenCL_MacProgGuide/Introduction/Introduction.html#//apple_ref/doc/uid/TP40008312-CH1-SW1) guide on OpenCL for MacOS    
 - [OpenCL - Open Language for Parralel Programs (Russian)](https://cmp.phys.msu.ru/sites/default/files/OpenCL.pdf) - introductory course into OpenCL    
    
## Final notes    
    
- If you choose to compile from sources (without **Makefile**), don't forget the `-framework OpenCL` flag.    
 - Be informed, that this project uses `<stdio.h>` and `<stdlib` includes.  
    
    
## Credit 
This project is based on the [OpenCL-Getting-Started](https://github.com/smistad/OpenCL-Getting-Started) project by Erik Smistad (@smistad).