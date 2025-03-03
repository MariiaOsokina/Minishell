NAME	= shell

SRC_PATH = src/
OBJ_PATH = obj/
SRC = main.c redirection.c error_msg.c simple_cmd_exec.c builtins/*.c

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
	mkdir -p $(OBJ_PATH) $(OBJ_PATH)/builtins/
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
		make clean -C ./libft
		rm -rf $(OBJ_PATH)

fclean: clean
		make fclean -C ./libft
		rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
