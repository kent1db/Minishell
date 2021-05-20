# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 14:11:52 by alafranc          #+#    #+#              #
#    Updated: 2021/05/20 10:50:08 by alafranc         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

FILES_DISPLAY	= print_banner.c
FILES_PARSING	= ft_parse_arg.c ft_parse_env.c
FILES_GENERAL	= ft_garbage_collector.c ft_error.c main.c
FILES_CMD		= ft_launch_cmd.c ft_lst_env.c ft_cli_env.c ft_utility_env.c ft_fill_array_our_cmd.c

FILES			= $(addprefix display/, ${FILES_DISPLAY}) \
				  ${addprefix parsing/, ${FILES_PARSING}} \
				  ${addprefix cmd/, ${FILES_CMD}} \
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