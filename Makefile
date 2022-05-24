# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 21:14:06 by aaljaber          #+#    #+#              #
#    Updated: 2022/05/23 18:47:29 by dfurneau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =   src/main.c src/mini_ctrls.c 
		src/mini_init.c src/mini_tools.c 
		src/mini_cmd.c src/mini_check.c 
		./mini_cmd_opt.c ./mini_cmd_arg.c
		./mini_parse.c

OBJ = ${SRC:.c=.o}

NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra  -I /usr/local/opt/readline/include

LINKS =  -L /usr/local/opt/readline/lib -lreadline

RM = rm -rf

all : ${NAME}

${NAME} : ${OBJ}
		${MAKE} -C ./libft
		${CC} ${SRC} ./libft/libft.a -o ${NAME} ${CFLAGS} ${LINKS} 

clean : 
		${RM} ${OBJ}
		${MAKE} clean -C ./libft

fclean : clean
		${RM} ${NAME}
		${MAKE} fclean -C ./libft
 
re : fclean all