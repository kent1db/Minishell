# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 14:11:52 by alafranc          #+#    #+#              #
#    Updated: 2021/05/21 13:30:05 by alafranc         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

FILES_PARSING	= parse_arg.c parse_env.c
FILES_GENERAL	= garbage_collector.c error.c main.c print_banner.c
FILES_CMD		= 
FILES_LAUNCH	= pointer_array_fct_cmd.c launch_cmd.c launch_execve.c
FILES_ENV		= cli_env.c lst_env.c

FILES			= $(addprefix display/, ${FILES_DISPLAY}) \
				  ${addprefix parsing/, ${FILES_PARSING}} \
				  ${addprefix cmd/, ${FILES_CMD} ${addprefix env/, ${FILES_ENV}} ${addprefix launch/, ${FILES_LAUNCH}}} \
				  ${FILES_GENERAL}
				  

INC_FILES		= minishell.h color.h struct.h
INC_PATH		= ./includes/
INC				= $(addprefix ${INC_PATH}, ${INC_FILES})

SRC_PATH		= srcs
SRC				= $(addprefix ${SRC_PATH}/, ${FILES})

OBJS_PATH		= objs
OBJS 			= $(addprefix $(OBJS_PATH)/, $(SRC:.c=.o))
OBJS_FINAL		= $(addprefix ${OBJS_PATH}/, $(notdir $(OBJS)))

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

$(OBJS_PATH)/%.o: %.c  $(INC)
				@$(CC) $(FLAGS) -I ${INC_PATH} -c $< -o $(addprefix ${OBJS_PATH}/, $(notdir $@))
				@printf "\e[?25l\e[JMINISHELL : \e[92m$(notdir $<)\e[0m\r"

${NAME}: 		init ${OBJS}
				@${CC} ${FLAGS} ${OBJS_FINAL} -o ${NAME} ${NAME_LIBFT} -I ${INC_PATH}
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