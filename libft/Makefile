# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 14:45:08 by niduches          #+#    #+#              #
#    Updated: 2020/01/05 09:13:45 by niduches         ###   ########.fr        #
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
			printf/ft_printf.c				\
			printf/conv_char.c				\
			printf/conv_hex.c				\
			printf/conv_int.c				\
			printf/conv_ptr.c				\
			printf/conv_str.c				\
			printf/conv_uhex.c				\
			printf/conv_uint.c				\
			printf/conv_nb_print_char.c	\
			printf/conv_float.c			\
			printf/conv_sct.c				\
			printf/conv_g.c				\
			printf/ft_get_flags.c			\
			printf/ft_isconv.c				\
			printf/ft_isflag.c				\
			printf/ft_makeconv.c			\
			printf/ft_putnstr.c			\
			printf/ft_put_long_nbr.c		\
			printf/conv_g_float.c			\
			printf/float_round.c			\

LIB_DIR	=	printf						\

LIB		=	printf/printf.a				\

OBJ		=	$(SRC:%.c=%.o)

CFLAGS	+=	-I./ -Wall -Wextra #-Werror

NAME	=	libft.a

all:	$(NAME)

clean:
	make -C $(LIB_DIR) clean
	rm -f $(OBJ)
	rm -f $(SRCB:%.c=%.o)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

$(NAME): $(OBJ)
#	make -C $(LIB_DIR)
	ar rc $(NAME) $(OBJ) # $(LIB)

re:	fclean $(NAME)

.PHONY: all clean fclean re
