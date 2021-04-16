# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/23 14:11:52 by alafranc          #+#    #+#              #
#    Updated: 2021/04/16 15:19:08 by alafranc         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			= 
FILES			= 
INC_FILES		= main.h
INC_PATH		= ./includes/
INC				= $(addprefix ${INC_PATH}, ${INC_FILES})
SRC_PATH		= ./srcs/
SRC				= $(addprefix ${SRC_PATH}, ${FILES})

CC				= clang
OBJS 			= ${SRC:.c=.o}
FLAGS			= -Wall -Wextra -Werror

#LIBRARY
NAME_LIBFT 		= libft.a
LIBFT_PATH 		= libft/
LIBFT			= $(addprefix ${LIBFT_PATH}, ${NAME_LIBFT})

all: 			${NAME}	

lib: 
				make -C ${LIBFT_PATH}
				cp ${LIBFT} .

%.o: %.c 		${INC}
				${CC} ${FLAGS} -c $< -o $@ -I ${INC_PATH}

${NAME}: 		lib ${OBJS}
				${CC} ${FLAGS} ${OBJS} $(addprefix ${SRC_PATH}, main.c) -o ${NAME} ${NAME_LIBFT} -I ${INC_PATH}

clean:
				make -C ${LIBFT_PATH} clean
				${RM} ${OBJS} ${OBJS_BONUS}

fclean:			clean
				${RM} ${NAME}
				${RM} ${LIBFT}
				${RM} ${NAME_LIBFT}
re:				fclean all


.PHONY: all clean fclean re lib