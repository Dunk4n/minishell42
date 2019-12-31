# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 14:45:08 by niduches          #+#    #+#              #
#    Updated: 2019/12/17 13:14:03 by niduches         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

SRC		=	ft_atoi.c					\
			ft_isalpha.c				\
			ft_isalnum.c				\
			ft_isascii.c				\
			ft_calloc.c					\
			ft_isdigit.c				\
			ft_isprint.c				\
			ft_isspace.c				\
			ft_bzero.c					\
			ft_itoa.c					\
			ft_memccpy.c				\
			ft_memchr.c					\
			ft_memcmp.c					\
			ft_memcpy.c					\
			ft_putchar_fd.c				\
			ft_putendl_fd.c				\
			ft_memmove.c				\
			ft_putstr_fd.c				\
			ft_putnbr_fd.c				\
			ft_strchr.c					\
			ft_strdup.c					\
			ft_strjoin.c				\
			ft_strlcat.c				\
			ft_strlen.c					\
			ft_memset.c					\
			ft_strncmp.c				\
			ft_strmapi.c				\
			ft_strrchr.c				\
			ft_strnstr.c				\
			ft_strtrim.c				\
			ft_tolower.c				\
			ft_toupper.c				\
			ft_split.c					\
			ft_substr.c					\
			ft_strlcpy.c				\
			ft_pow.c					\
			ft_revstr.c					\
			ft_strcat.c					\
			ft_strncat.c				\
			ft_strcmp.c					\
			ft_strcpy.c					\
			ft_strncpy.c				\
			get_next_line.c				\

LIB_DIR	=	printf						\

LIB		=	printf/printf.a				\

OBJ		=	$(SRC:%.c=%.o)

CFLAGS	+=	-g -Wall -Wextra #-Werror

NAME	=	libft.a

all:	$(NAME)
	make -C $(LIB_DIR)

clean:
	make -C $(LIB_DIR) clean
	rm -f $(OBJ)
	rm -f $(SRCB:%.c=%.o)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	@ar rcT $(NAME) $(OBJ) $(LIB)

re:	fclean $(NAME)

.PHONY: all clean fclean re
