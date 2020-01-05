# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: niduches <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 19:02:16 by niduches          #+#    #+#              #
#    Updated: 2020/01/05 10:30:42 by niduches         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

D_SRC		=	./src/
D_SRC_BONUS	=	$(D_SRC)bonus/
D_INC		=	./include/
D_LIB		=	./libft/

BUILD_DIR	=	build

SRC_PATH	=	main.c					\
				init.c					\
				exit.c					\
				echo.c					\
				get_env.c				\
				env.c					\
				pwd.c					\
				get_all_instruction.c	\
				export.c				\
				unset.c					\
				to_line_env.c			\
				put_in_line.c			\
				get_var_len.c			\
				custom_split_instr.c	\
				custom_split_arg.c		\
				custom_split_sep.c		\
				get_nb_sep.c			\
				custom_split_sep_pipe.c	\
				get_nb_sep_pipe.c		\
				in_str.c				\
				exec_bin.c				\
				get_exec_path.c			\
				cd.c					\

SRC = $(addprefix $(D_SRC),$(SRC_PATH))

SRC_PATH_BONUS	=	

SRC_BONUS = $(addprefix $(D_SRC_BONUS),$(SRC_PATH_BONUS))

NAME	=	minishell

OBJ			=	$(SRC:%.c=$(BUILD_DIR)/%.o)
OBJ_BONUS	=	$(SRC_BONUS:%.c=$(BUILD_DIR)/%.o)

CFLAGS	=	-I$(D_INC) -Wall -Wextra #-Werror

LDFLAGS	=	-L./libft/ -lft

all:	$(NAME)

options:
	@echo "  CC       $(CC)"
	@echo "  CFLAGS   $(CFLAGS)"
	@echo "  LDFLAGS  $(LDFLAGS)"

$(BUILD_DIR)/%.o: %.c $(INC)
	@mkdir -p $(@D)
	@echo "  CC       $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(D_LIB) clean --no-print-directory
	@echo "  RM       $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@$(MAKE) -C $(D_LIB) fclean --no-print-directory
	@echo "  RM       $(NAME)"
	@rm -f $(NAME) *~

lib:
	echo $(D_LIB)
	@make -C $(D_LIB) --no-print-directory

$(NAME): lib options $(OBJ)
	@echo "  BUILD    $@"
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

bonus: lib options $(OBJ_BONUS)
	@echo "  BUILD    $@"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BONUS) $(LDFLAGS)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all options lib clean fclean re bonus
