NAME = libcl.a

SRC_DIR = ./srcs/
SRC =		assembly.c\
			build.c\
			libcl.c\
			clean_up.c\
			execute_kernel.c\
			get_dev_info.c\
			init_cl.c

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

INC = 		libcl.h\
			cl_structs.h\
			cl_user_structs.h

INC_DIR = ./includes/
INCS = $(addprefix $(INC_DIR), $(INC))

FLAGS = -g -Wall -Werror -Wextra -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJS)
		@ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
		gcc $(FLAGS) -o $@ -c $<

clean:
		@rm -f $(OBJS)
		@rm -rf $(OBJ_DIR)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re