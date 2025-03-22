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
SRCS         := $(BUILTINS_SRC) $(EXEC_SRC) main_andif_or.c

# Define object file paths that mirror the source structure
BUILTINS_OBJ := $(patsubst src/builtins/%.c,obj/builtins/%.o,$(BUILTINS_SRC))
EXEC_OBJ     := $(patsubst src/exec/%.c,obj/exec/%.o,$(EXEC_SRC))
MAIN_OBJ     := $(patsubst %.c,obj/%.o,$(filter-out $(BUILTINS_SRC) $(EXEC_SRC),$(SRCS)))
OBJS         := $(BUILTINS_OBJ) $(EXEC_OBJ) $(MAIN_OBJ)

# Make sure obj directory and subdirectories exist
OBJ_DIRS     := obj obj/builtins obj/exec

all: $(NAME)

# Create obj directories
$(OBJ_DIRS):
	@mkdir -p $@

# Rule for main program objects
obj/%.o: %.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule for builtins objects
obj/builtins/%.o: src/builtins/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule for exec objects
obj/exec/%.o: src/exec/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -lreadline

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -rf obj

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

debug:
	@echo "BUILTINS_SRC: $(BUILTINS_SRC)"
	@echo "EXEC_SRC: $(EXEC_SRC)"
	@echo "All SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"

re: fclean all

.PHONY: all clean fclean re $(OBJ_DIRS)
