# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 21:14:06 by aaljaber          #+#    #+#              #
#    Updated: 2022/06/28 12:57:52 by aaljaber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =   src/main.c                  		    src/mini_ctrls.c \
		src/mini_init.c           		      	src/mini_tools.c \
		src/mini_cmd.c              		    src/mini_check.c \
		src/mini_cmd_opt.c            			src/mini_cmd_arg.c \
		src/mini_cmd2.c               			src/mini_parse.c \
		src/mini_run_cmd.c             			src/mini_free.c \
		src/mini_envar.c                		src/mini_envar_tools.c \
		src/mini_envar_export.c           		src/mini_envar_unset.c \
		src/mini_echo_tools.c               	src/mini_cd_tools.c \
		src/mini_quotes_split.c         	    src/mini_quotes_checker.c \
		src/mini_envar_export_tools.c			src/mini_expand_tools.c \
		src/mini_expand_pre.c 					src/mini_expand_envar.c \
		src/mini_expand_action.c      			src/mini_echo_parse.c \
		src/mini_pre_execute.c					src/mini_run.c\
		src/mini_execute.c

OBJ = ${SRC:.c=.o}

NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -I /usr/local/opt/readline/include

LINKS =  -L /usr/local/opt/readline/lib -lreadline

RM = rm -rf

all : ${NAME}

.c.o :
	@ ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	
${NAME} :  ${OBJ}
	@ ${MAKE} -C ./libft
	@ ${CC} ${SRC} ./libft/libft.a -o ${NAME} ${CFLAGS} ${LINKS}
	@ afplay WAKUWAKU.mp3
# 	@ printf " \
# ,---.    ,---..-./`) ,---.   .--..-./`)             _______   .---.  .---.    ____    ,---.   .--. \
# |    \  /    |\ .-.')|    \  |  |\ .-.')           /   __  \  |   |  |_ _|  .'  __ `. |    \  |  | \
# |  ,  \/  ,  |/ `-' \|  ,  \ |  |/ `-' \          | ,_/  \__) |   |  ( ' ) /   '  \  \|  ,  \ |  | \
# |  |\_   /|  | `-'`"\`|  |\_ \|  | `-'`"\`        ,-./  )       |   '-(_{;}_)|___|  /  ||  |\_ \|  | \
# |  _( )_/ |  | .---. |  _( )_\  | .---.         \  '_ '`)     |      (_,_)    _.-`   ||  _( )_\  | \
# | (_ o _) |  | |   | | (_ o _)  | |   |          > (_)  )  __ | _ _--.   | .'   _    || (_ o _)  | \
# |  (_,_)  |  | |   | |  (_,_)\  | |   |         (  .  .-'_/  )|( ' ) |   | |  _( )_  ||  (_,_)\  | \
# |  |      |  | |   | |  |    |  | |   |          `-'`-'     / (_{;}_)|   | \ (_ o _) /|  |    |  | \
# '--'      '--' '---' '--'    '--' '---'            `._____.'  '(_,_) '---'  '.(_,_).' '--'    '--' "

clean : 
	@ ${RM} ${OBJ}
	@ ${MAKE} clean -C ./libft

fclean : clean
	@ ${RM} ${NAME}
	@ ${MAKE} fclean -C ./libft
 
re : fclean all