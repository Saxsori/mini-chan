#include <sys/_types/_pid_t.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 #include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
# include "../libft/libft.h"


// int main(int ac , char *av[])
// {
// 	int fd;
// 	char *dlm;
// 	char **c ;
// 	c= ft_split(av[4], '\0');
// 	printf(" str .. %s",c[0]);
// 	fd = open(av[1],O_CREAT | O_RDWR);
// 	if(access(av[1],F_OK)< 0)
// 		printf("%s NOT CREATED!!!\n",av[1]);
// 	else
// 		printf("%s CREATED\n",av[1]);
// 	if(av[2][0] == '<')
// 	{
// 		while(1)
// 		{
// 			dlm = readline(">");
// 			// dup2(STDIN_FILENO,fd);
// 			if(!strcmp(dlm,av[3]))
// 			{
// 				if(execve(av[5],c,NULL) < 0)
// 					perror(strerror(errno));
// 				break;
// 			}
// 		}
// 	}
// 	if(unlink(av[1]) == 0)
// 		printf("%s deleted!!! \n",av[1]);
// 	else
// 	 	printf("%s 	NOT deleted \n",av[1]);
// 	close(fd);
// 	return (0);
// }



int main(int ac,char *av[])
{
	int fd[2];
	int stat;
	char **c = ft_split(av[1], '\0');
	if(pipe(fd) < 0)
		perror("pipe error");
	pid_t child = fork();
	if(child == 0)
	{
		dup2(STDOUT_FILENO,fd[1]);
		if(execve("bin/ls",c, NULL) < 0)
			perror("error");
		dup2(STDIN_FILENO,fd[0]);
		if(execve("bin/ls",c, NULL) < 0)
			perror("error2");
	}
	else {
		waitpid(0, &stat, 0);
	}
}