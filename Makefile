NAME = cl_test

SRC = main.c

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

CL_OBJ = *.o
CL_OBJ_DIR = ./opencl_primer/obj/
CL_OBJS = $(addprefix $(CL_OBJ_DIR), $(CL_OBJ))
CL_SRC_DIR = ./opencl_primer/srcs/

CL_INC = 	cl_primer.h\
			cl_structs.h\
			cl_user_structs.h

CL_INC_DIR = ./opencl_primer/includes/
CL_INCS = $(addprefix $(CL_INC_DIR), $(CL_INC))

LIBRARIES = -framework OpenCL

FLAGS = -g -Wall -Wextra -Werror -I$(CL_INC_DIR)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(CL_OBJS) $(OBJS)
		@gcc $(OBJS) ./opencl_primer/opencl_primer.a -o $(NAME) $(LIBRARIES)

$(OBJ_DIR):
		@mkdir -p $@
		@mkdir -p $(CL_OBJ_DIR)

$(CL_OBJ_DIR)%.o: $(CL_SRC_DIR)%.c $(CL_INCS)
		@make -C opencl_primer

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		gcc $(FLAGS) -o $@ -c $<

clean:
		@make clean -C opencl_primer
		@rm -f $(OBJS)
		@rm -rf $(OBJ_DIR)

fclean: clean
		@make fclean -C opencl_primer
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re