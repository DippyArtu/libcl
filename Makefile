NAME = cl_test

SRC = main.c

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

CL_OBJ = *.o
CL_OBJ_DIR = ./libcl/obj/
CL_OBJS = $(addprefix $(CL_OBJ_DIR), $(CL_OBJ))
CL_SRC_DIR = ./libcl/srcs/

CL_INC = 	libcl.h\
			cl_structs.h\
			cl_user_structs.h

CL_INC_DIR = ./libcl/includes/
CL_INCS = $(addprefix $(CL_INC_DIR), $(CL_INC))

LIBRARIES = -framework OpenCL

FLAGS = -g -Wall -Wextra -Werror -I$(CL_INC_DIR)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(CL_OBJS) $(OBJS)
		@gcc $(OBJS) ./libcl/libcl.a -o $(NAME) $(LIBRARIES)

$(OBJ_DIR):
		@mkdir -p $@
		@mkdir -p $(CL_OBJ_DIR)

$(CL_OBJ_DIR)%.o: $(CL_SRC_DIR)%.c $(CL_INCS)
		@make -C libcl

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		gcc $(FLAGS) -o $@ -c $<

clean:
		@make clean -C libcl
		@rm -f $(OBJS)
		@rm -rf $(OBJ_DIR)

fclean: clean
		@make fclean -C libcl
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re