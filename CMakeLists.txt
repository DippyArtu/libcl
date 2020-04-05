cmake_minimum_required(VERSION 3.15)
project(libcl C)

set(CMAKE_C_STANDARD 11)

include_directories(libcl/includes
        kernel_includes)

add_library(libcl
        libcl/includes/libcl.h
        libcl/includes/cl_structs.h
        libcl/includes/cl_user_structs.h
        libcl/srcs/libcl.c
        libcl/srcs/build.c
        libcl/srcs/get_dev_info.c
        libcl/srcs/assembly.c
        libcl/srcs/execute_kernel.c
        libcl/srcs/init_cl.c
        libcl/srcs/clean_up.c
        kernels/kernel.cl
        kernel_includes/kernel_structs.h
        main.c libcl/includes/cl_errors.h)

