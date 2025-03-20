NAME        := minishell

LIBFT       := libft.a
LIBFT_PATH  := libft/

CC          := cc
CFLAGS      := -Wall -Werror -Wextra
INCLUDES    := -I includes

# If you need to specify a custom path for readline
# READLINE_PATH := /goinfre/homebrew/opt/readline
# INCLUDES      += -I$(READLINE_PATH)/include
# LDFLAGS       := -L$(READLINE_PATH)/lib

BUILTINS_SRC := $(wildcard src/builtins/*.c)
EXEC_SRC     := $(wildcard src/exec/*.c)
SRCS         := $(BUILTINS_SRC) $(EXEC_SRC) main_pipes.c

# Generate list of object files
OBJS         := $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

debug:
	@echo "BUILTINS_SRC: $(BUILTINS_SRC)"
	@echo "EXEC_SRC: $(EXEC_SRC)"
	@echo "All SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"

re: fclean all

.PHONY: all clean fclean re
