NAME		:= minishell

# LIBFT		:= libft.a
# LIBFT_PATH	:= "libft/"

CC			:= cc

CFLAGS		:= -Wall -Werror -Wextra

BUILTINS	:=	builtins/*.c

# CLEANING	:=	cleaning/ft_clean_ms.c

EXEC		:=	exec/*.c

SRCS		:=	$(BUILTINS)\
				$(EXEC)\
				main_simple_cmd.c

OBJS		:=	$(SRCS:.c=.o)

HEADER = -I includes

# READLINE_PATH:=	/goinfre/homebrew/opt/readline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
