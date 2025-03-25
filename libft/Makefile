# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 17:09:42 by aaladeok          #+#    #+#              #
#    Updated: 2025/03/24 00:03:08 by mosokina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
	ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strdup.c ft_strchr.c ft_strcmp.c \
	ft_strrchr.c ft_atoi.c ft_strnstr.c ft_strmapi.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_itoa.c ft_striteri.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_calloc.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstdelone.c \
			  ft_lstiter.c ft_lstadd_back.c ft_lstclear.c ft_lstmap.c ft_strndup.c\

# BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstdelone.c \
# 			  ft_lstiter.c ft_lstadd_back.c ft_lstclear.c ft_lstmap.c \

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBC = ar rcs
OBJS = $(SRCS:.c=.o)
# BONUS_OBJS = $(BONUS_SRC:.c=.o)
RM = rm -rf

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)


# bonus: $(OBJS) $(BONUS_OBJS)
# 	$(LIBC) $(NAME) $(BONUS_OBJS) $(OBJS)

%.c%.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

clean: 
	@$(RM) $(OBJS)

# clean: 
# 	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean re fclean all