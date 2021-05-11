# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 14:11:52 by alafranc          #+#    #+#              #
#    Updated: 2021/05/11 15:26:39 by alafranc         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

FILES_DISPLAY	= print_banner.c
FILES_PARSING	= ft_parse_arg.c ft_parse_env.c
FILES_ENV		= ft_lst_env.c ft_cli_env.c ft_utility_env.c
FILES_GENERAL	= ft_garbage_collector.c ft_error.c main.c

FILES			= $(addprefix display/, ${FILES_DISPLAY}) \
				  ${addprefix env/, ${FILES_ENV}} \
				  ${addprefix parsing/, ${FILES_PARSING}} \
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
				$(shell mkdir -p $(OBJS_PATH))
				make -C ${LIBFT_PATH}
				cp ${LIBFT} .

$(OBJS_PATH)/%.o: %.c  $(INC)
				$(CC) $(FLAGS) -I ${INC_PATH} -c $< -o $(addprefix ${OBJS_PATH}/, $(notdir $@))

${NAME}: 		init ${OBJS}
				${CC} ${FLAGS} ${OBJS_FINAL} -o ${NAME} ${NAME_LIBFT} -I ${INC_PATH}

clean:
				make -C ${LIBFT_PATH} clean
				${RM} ${OBJS_PATH}

fclean:			clean
				make -C ${LIBFT_PATH} fclean
				${RM} ${NAME_LIBFT}
				
re:				fclean all

.PHONY: all clean fclean re bonus init