SRC = src/main.c src/mini_ctrls.c src/mini_init.c
OBJ = ${SRC:.c=.o}

NAME = minishell

CC = gcc
# -I /usr/local/opt/readline/include
CFLAGS = -Wall -Werror -Wextra
# -L /usr/local/opt/readline/lib
LINKS = -lreadline 

RM = rm -rf

all : ${NAME}

${NAME} : ${OBJ}
		${MAKE} -C ./libft
		gcc ${OBJ} ./libft/libft.a ${LINKS} -o ${NAME}

clean : 
		${RM} ${OBJ}
		${MAKE} clean -C ./libft

fclean : clean
		${RM} ${NAME}
		${MAKE} fclean -C ./libft
 
re : fclean all