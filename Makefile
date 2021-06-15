# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 14:11:52 by alafranc          #+#    #+#              #
#    Updated: 2021/06/15 17:26:26 by alafranc         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

FILES_GENERAL	= garbage_collector.c error.c main.c display.c 
FILES_EXEC		= exec_line.c ft_file.c ft_pipe.c ft_redir.c
FILES_LAUNCH	= pointer_array_fct_cmd.c launch_cmd.c launch_execve.c
FILES_CMD		= exit.c  easter_egg.c cd.c
FILES_ECHO		= echo.c utility_echo.c
FILES_ENV		= export_unset.c utility_lst_env.c convert_env_to_strs.c env.c
FILES_TERMCAP	= arrow_key.c delete.c init_terms.c print_buf_and_stock.c \
				  read_cmd_line.c termios.c utility.c reset_line_and_stock.c
FILES_PARSING	= utils_parsing.c cmd_parsing.c env_parsing.c file_parsing.c parsing.c print.c priority_op.c redir_parsing.c
FILES_ARG		= parse_argument.c quote.c ft_split_quote.c is_backslash.c backslash.c utility_arg.c

FILES			= $(addprefix display/, ${FILES_DISPLAY}) \
				  ${addprefix exec/, ${FILES_EXEC}} \
				  ${addprefix parsing/, ${FILES_PARSING}} \
				  ${addprefix cmd/, ${FILES_CMD} ${addprefix env/, ${FILES_ENV}} ${addprefix launch/, ${FILES_LAUNCH}} ${addprefix echo/, ${FILES_ECHO}}} \
				  ${addprefix termcap/, ${FILES_TERMCAP}} \
				  ${addprefix special_char/, ${FILES_QUOTES}} \
				  ${addprefix arg/, ${FILES_ARG}} \
				  ${FILES_GENERAL}

INC_FILES		= minishell.h color.h struct.h
INC_PATH		= ./includes/
INC				= $(addprefix ${INC_PATH}, ${INC_FILES})

SRC_PATH		= srcs
SRC				= $(addprefix ${SRC_PATH}/, ${FILES})

BIN_PATH		= bin
BIN 			= $(SRC:%.c=$(BIN_PATH)/%.o)

NAME_LIBFT 		= libft.a
LIBFT_PATH 		= libft/
LIBFT			= $(addprefix ${LIBFT_PATH}, ${NAME_LIBFT})

CC				= clang
RM				= rm -rf
FLAGS			= -fsanitize=address #-Wall -Wextra  -Werror

all: 			${NAME}

init:
				@$(shell mkdir -p $(BIN_PATH))
				@make -C ${LIBFT_PATH}
				@cp ${LIBFT} .


$(BIN): $(BIN_PATH)/%.o: %.c ${INC}
				@mkdir -p $(@D)
				@$(CC) $(FLAGS) -I ${INC_PATH} -o $@ -c $<
				@printf "\e[?25l\e[JMINISHELL : \e[92m$(notdir $<)\e[0m\r"

${NAME}: 		init ${BIN}
				@${CC} ${FLAGS} -lreadline -L/Users/alafranc/.brew/opt/readline/lib -I/Users/alafranc/.brew/opt/readline/include ${BIN} -o ${NAME} ${NAME_LIBFT} -I ${INC_PATH} -lncurses
				@printf '\033[?25l\033[JMINISHELL CREATED \033[92m✔ \033[0m\033[?25h\n'

clean:
				@make -C ${LIBFT_PATH} clean
				@${RM} ${BIN_PATH}
				@printf '\033[?25l\033[JMINISHELL DELETED \033[92m✔ \033[0m\033[?25h\n'

fclean:			
				@make -C ${LIBFT_PATH} fclean
				@${RM} ${NAME_LIBFT}
				@${RM} ${BIN_PATH}
				@${RM} ${NAME}
				@printf '\033[?25l\033[JMINISHELL DELETED \033[92m✔ \033[0m\033[?25h\n'
				
re:				fclean all

.PHONY: all clean fclean re bonus init