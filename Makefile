#colors
RED    = $(shell printf "\33[31m")
GREEN  = $(shell printf "\33[32m")
WHITE  = $(shell printf "\33[37m")
YELLOW = $(shell printf "\33[33m")
RESET  = $(shell printf "\33[0m")
BLUE   = $(shell printf "\33[34m")
PURPLE = $(shell printf "\33[35m")
TITLE  = $(shell printf "\33[32;40m")

NAME = minishell
LIBFTDIR = libft
FLAGS = -Wall -Werror -Wextra -g -Iinclude #-fsanitize=address
IFLAGS = -Iinclude/ -I${LIBFTDIR}
CC = gcc
SRCS = $(wildcard srcs/*.c) $(wildcard srcs/*/*.c)
OBJS = ${SRCS:.c=.o}
INCLUDE = -L${LIBFTDIR} -lft -lreadline
VALGRIND = valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=readline.supp
ENV = env -i ${VALGRIND}

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	INCLUDE = -L${LIBFTDIR} -lft -readline -lhistory
	READLINE =
else ifeq ($(UNAME), Darwin)
	INCLUDE = -L${LIBFTDIR} -lft -L/opt/homebrew/opt/readline/lib -lreadline
	READLINE = -I/opt/homebrew/opt/readline/include
endif

all: ${LIBFTDIR} ${NAME} ${OBJS}

# submodule:
# 	@git submodule update --init --recursive

${NAME}:	${OBJS}
	@make --silent -C ${LIBFTDIR}
	@${CC} ${FLAGS} ${READLINE} ${OBJS} ${INCLUDE} -o ${NAME}
	@echo "$(TITLE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "$(PURPLE)  ███╗   ███╗██╗███╗   ██╗██╗██╗  ██╗███████╗██╗     ██╗       "
	@echo "  ████╗ ████║██║████╗  ██║██║██║  ██║██╔════╝██║     ██║       "
	@echo "  ██╔████╔██║██║██╔██╗ ██║██║███████║█████╗  ██║     ██║       "
	@echo "  ██║╚██╔╝██║██║██║╚██╗██║██║██╔══██║██╔══╝  ██║     ██║       "
	@echo "  ██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║███████╗███████╗███████╗  "
	@echo "  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝  "
	@echo "$(GREEN)━━━━━━━━━━━━━━━━━[$(RESET)Made with $(RED)♥ $(RESET)by $(PURPLE)@aladeok$(RESET) and $(PURPLE)@mosokina$(TITLE)]━━━━━━"
	@echo
	@echo "$(GREEN) Successfully compiled minishell.$(RESET)"
	@echo

.c.o:
	@$(CC) ${FLAGS} ${READLINE} ${IFLAGS} -c $< -o ${<:.c=.o}
	@clear
	@echo "$(RESET)[$(GREEN)OK$(RESET)]$(BLUE) compiling $<$(YELLOW)"

clean:
	@${RM} ${OBJS} ${NAME}
	@cd ${LIBFTDIR} && $(MAKE) --silent fclean
	@clear
	@echo
	@echo "$(RED)┏┓┓ ┏┓┏┓┳┓┏┓┳┓"
	@echo "┃ ┃ ┣ ┣┫┃┃┣ ┃┃"
	@echo "┗┛┗┛┗┛┛┗┛┗┗┛┻┛" $(RESET)
	@echo

fclean: clean
	rm -f ${NAME}
	@clear
	@echo
	@echo "$(RED)┏┓┓ ┏┓┏┓┳┓┏┓┳┓"
	@echo "┃ ┃ ┣ ┣┫┃┃┣ ┃┃"
	@echo "┗┛┗┛┗┛┛┗┛┗┗┛┻┛" $(RESET)
	@echo

test: ${NAME} readline.supp
	${VALGRIND} ./${NAME}

readline.supp:
	@echo "Generating readline.supp..."
	@cat <<EOF > readline.supp
	{
			leak readline
			Memcheck:Leak
			...
			fun:readline
	}
	{
			leak add_history
			Memcheck:Leak
			...
			fun:add_history
	}
	{
			leak rl_parse_and_bind
			Memcheck:Leak
			...
			fun:rl_parse_and_bind
	}
	EOF

env: ${NAME}
	${ENV} ./${NAME}

re: fclean all

.PHONY: all bonus clean fclean re test
# readline.supp:
# 	echo "{" > readline.supp
# 	echo "    leak readline" >> readline.supp
# 	echo "    Memcheck:Leak" >> readline.supp
# 	echo "    ..." >> readline.supp
# 	echo "    fun:readline" >> readline.supp
# 	echo "}" >> readline.supp
# 	echo "{" >> readline.supp
# 	echo "    leak add_history" >> readline.supp
# 	echo "    Memcheck:Leak" >> readline.supp
# 	echo "    ..." >> readline.supp
# 	echo "    fun:add_history" >> readline.supp
# 	echo "}" >> readline.supp
# 	echo "{" >> readline.supp
# 	echo "    leak rl_parse_and_bind" >> readline.supp
# 	echo "    Memcheck:Leak" >> readline.supp
# 	echo "    ..." >> readline.supp
# 	echo "    fun:add_history" >> readline.supp
# 	echo "}" >> readline.supp
