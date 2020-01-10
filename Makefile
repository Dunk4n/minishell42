# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cal-hawa <cal-hawa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 19:02:16 by niduches          #+#    #+#              #
#    Updated: 2020/01/10 15:13:10 by cal-hawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

D_SRC		=	./src/
D_SRC_BONUS	=	$(D_SRC)bonus/
D_INC		=	./include/
D_LIB		=	./libft/

BUILD_DIR	=	build

SRC_PATH	=	main.c						\
				init.c						\
				exit.c						\
				echo.c						\
				get_env.c					\
				env.c						\
				pwd.c						\
				get_all_instruction.c		\
				export.c					\
				unset.c						\
				to_line_env.c				\
				put_in_line.c				\
				get_var_len.c				\
				custom_split_instr.c		\
				custom_split_arg.c			\
				custom_split_sep.c			\
				get_nb_sep.c				\
				custom_split_sep_pipe.c		\
				get_nb_sep_pipe.c			\
				in_str.c					\
				exec_bin.c					\
				get_exec_path.c				\
				cd.c						\

CAL_PATH	=	exec_command.c				\
				exec_standalone.c			\
				parse_process_quote.c		\
				parse_str_trim.c			\
				exec_mpipeline.c			\
				parse_split_arguments.c		\
				exec_redirections.c			\
				exec_arguments.c			\
				parse_command.c				\
				parse_split_redirections.c	\
				built_in.c					\
				execve_wrapper.c

SRC = $(addprefix $(D_SRC),$(SRC_PATH))
CAL = $(addprefix ./cal-hawa/,$(CAL_PATH))
SRC += $(CAL)

SRC_PATH_BONUS	=	bonus/main_bonus.c					\
					bonus/init_bonus.c					\
					bonus/exit_bonus.c					\
					bonus/cursor_utils_bonus.c			\
					bonus/get_edit_line_bonus.c			\
					bonus/line_editing_bonus.c			\
					bonus/line_editing_command_bonus.c	\
					bonus/add_in_history_bonus.c		\
					echo.c								\
					get_env.c							\
					env.c								\
					pwd.c								\
					get_all_instruction.c				\
					export.c							\
					unset.c								\
					to_line_env.c						\
					put_in_line.c						\
					get_var_len.c						\
					custom_split_instr.c				\
					custom_split_arg.c					\
					custom_split_sep.c					\
					get_nb_sep.c						\
					custom_split_sep_pipe.c				\
					get_nb_sep_pipe.c					\
					in_str.c							\
					exec_bin.c							\
					get_exec_path.c						\
					cd.c								\

SRC_BONUS = $(addprefix $(D_SRC),$(SRC_PATH_BONUS))
SRC_BONUS += $(CAL)

NAME	=	minishell

OBJ			=	$(SRC:%.c=$(BUILD_DIR)/%.o)
OBJ_BONUS	=	$(SRC_BONUS:%.c=$(BUILD_DIR)/%.o)

CFLAGS	=	-I$(D_INC) -Wall -Wextra #-Werror

LDFLAGS	=	-L./libft/ -lft -ltermcap

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

bonus: fclean lib options $(OBJ_BONUS)
	@echo "  BUILD    $@"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BONUS) $(LDFLAGS)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

.PHONY: all options lib clean fclean re bonus
