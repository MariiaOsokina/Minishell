NAME	= shell

SRC_PATH = src/ builtins/
OBJ_PATH = obj/ obj/builtins/
SRC = *.c
# main.c redirection.c error_msg.c simple_cmd_exec.c 
# builtins/builtins_all.c builtins/builtin_cd.c builtins/builtin_echo.c builtins/builtin_env.c builtins/builtin_unset.c \
# builtins/builtin_export builtins/builtin_pwd.c builtins/builtin_utils.c 
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ 	= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror
HEADER = -I includes

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(OBJS) -L ./libft -lft -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
		make clean -C ./libft
		rm -rf $(OBJ_PATH)

fclean: clean
		make fclean -C ./libft
		rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
