SRC = src/main.c src/mini_ctrls.c src/mini_init.c src/mini_tools.c

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