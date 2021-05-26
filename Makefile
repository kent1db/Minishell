# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 14:11:52 by alafranc          #+#    #+#              #
#    Updated: 2021/05/26 16:28:05 by alafranc         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

FILES_PARSING	= parse_arg.c parse_env.c
FILES_GENERAL	= garbage_collector.c error.c main.c print_banner.c
FILES_LAUNCH	= pointer_array_fct_cmd.c launch_cmd.c launch_execve.c
FILES_ENV		= cli_env.c lst_env.c
FILES_TERMCAP	= termios.c history.c pick_signal.c termcap.c terms.c

FILES			= $(addprefix display/, ${FILES_DISPLAY}) \
				  ${addprefix parsing/, ${FILES_PARSING}} \
				  ${addprefix cmd/, ${FILES_CMD} ${addprefix env/, ${FILES_ENV}} ${addprefix launch/, ${FILES_LAUNCH}}} \
				  ${addprefix termcap/, ${FILES_TERMCAP}} \
				  ${FILES_GENERAL}

INC_FILES		= minishell.h color.h struct.h
INC_PATH		= ./includes/
INC				= $(addprefix ${INC_PATH}, ${INC_FILES})

SRC_PATH		= srcs
SRC				= $(addprefix ${SRC_PATH}/, ${FILES})

OBJS_PATH		= objs
OBJS 			= $(SRC:%.c=$(OBJS_PATH)/%.o)

NAME_LIBFT 		= libft.a
LIBFT_PATH 		= libft/
LIBFT			= $(addprefix ${LIBFT_PATH}, ${NAME_LIBFT})

CC				= clang
RM				= rm -rf
FLAGS			= #-Wall -Wextra -Werror 

all: 			${NAME}

init:
				@$(shell mkdir -p $(OBJS_PATH))
				@make -C ${LIBFT_PATH}
				@cp ${LIBFT} .


$(OBJS): $(OBJS_PATH)/%.o: %.c ${INC}
				@mkdir -p $(@D)
				@$(CC) $(FLAGS) -I ${INC_PATH} -o $@ -c $<
				@printf "\e[?25l\e[MINISHELL : \e[92m$(notdir $<)\e[0m\r"

${NAME}: 		init ${OBJS}
				@${CC} ${FLAGS} ${OBJS} -o ${NAME} ${NAME_LIBFT} -I ${INC_PATH} -lncurses
				@printf '\033[?25l\033[JMINISHELL CREATED \033[92m✔ \033[0m\033[?25h\n'

clean:
				@make -C ${LIBFT_PATH} clean
				@${RM} ${OBJS_PATH}

fclean:			
				@make -C ${LIBFT_PATH} fclean
				@${RM} ${NAME_LIBFT}
				@${RM} ${OBJS_PATH}
				@${RM} ${NAME}
				
re:				fclean all

.PHONY: all clean fclean re bonus init