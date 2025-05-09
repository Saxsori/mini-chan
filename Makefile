# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: balnahdi <balnahdi@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 21:14:06 by aaljaber          #+#    #+#              #
#    Updated: 2022/09/14 17:42:07 by balnahdi         ###   ########.fr        #                                                                              #
# **************************************************************************** #

SRC =   src/main.c                  		    src/mini_ctrls.c \
		src/mini_init.c           		      	src/mini_tools.c \
		src/mini_cmd_split.c\
		src/mini_cmd.c              		    src/mini_check.c \
		src/mini_cmd_opt.c            			src/mini_cmd_arg.c \
		src/mini_cmd2.c               			src/mini_parse.c \
		src/mini_run_cmd.c             			src/mini_free.c \
		src/mini_envar.c                		src/mini_envar_tools.c \
		src/mini_envar_export.c           		src/mini_envar_unset.c \
		src/mini_echo_tools.c               	src/mini_cd_tools.c \
		src/mini_cd_do.c \
		src/mini_quotes_split.c         	    src/mini_quotes_checker.c \
		src/mini_quotes_split_tools.c\
		src/mini_envar_export_tools.c			src/mini_expand_tools.c \
		src/mini_expand_pre.c 					src/mini_expand_envar.c \
		src/mini_expand_action.c				src/mini_expand_1dollar_case.c \
		src/mini_expand_find_env.c\
		src/mini_pre_execute.c					src/mini_run.c \
		src/mini_execute.c						src/mini_redir_tools.c \
		src/mini_redir_pre.c					src/mini_redir_isvalid.c \
		src/mini_redir_take_valid.c             src/mini_redir_getredir.c \
		src/mini_redir_reline.c					src/mini_redir_split.c \
		src/mini_redir_get_parts.c              src/mini_redir_check.c \
		src/mini_redir_get_arg.c\
		src/mini_pipe.c							src/mini_redir.c \
		src/mini_redir_opt.c					src/mini_exit_pre.c \
		src/mini_heredoc.c 						src/mini_exit_tools.c \
		src/mini_pipe_tools.c \
		src/mini_pipe_pre.c						src/mini_special_null_case.c \
		src/mini_redir_get_cmd.c                src/mini_errormng.c \
		src/mini_wait.c							src/mini_pipe_tools_path.c \
		src/mini_pipe_exe.c						src/mini_builtin_tools.c\
		src/mini_unset_tools.c					src/mini_run_one_redir.c\
		src/mini_init_redir.c					src/mini_init_cmd.c \
		src/mini_init_small_parse.c             src/mini_free_tools.c \
		src/mini_free_redir.c					src/mini_exe_err.c \

OBJ = ${SRC:.c=.o}

NAME = minishell

CC = gcc

SANITIZE = -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
# -I /usr/local/opt/readline/include
CFLAGS = -Wall -Werror -Wextra -g -I /usr/local/opt/readline/include 

#-L /usr/local/opt/readline/lib
LINKS =  -lreadline -L /usr/local/opt/readline/lib

RM = rm -rf

all : ${NAME}

.c.o :
	@ ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	
${NAME} :  ${OBJ}
	@ ${MAKE} -C ./libft
	@ ${CC} ${SRC} ./libft/libft.a -o ${NAME} ${CFLAGS} ${LINKS}
	@ afplay ./tools/WAKUWAKU.mp3
	@ tput setaf 4 
	@ cat ./tools/minichan.txt
	@ tput setaf default

clean : 
	@ ${RM} ${OBJ}
	@ ${MAKE} clean -C ./libft

fclean : clean
	@ ${RM} ${NAME}
	@ ${MAKE} fclean -C ./libft
 
re : fclean all