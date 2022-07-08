#include "../mini_chan.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void path(t_shell_chan *main,char *av[],int argc)
{
	t_mini_envar *envar;
	char	*path;
	int i = 0;
	envar = search_envar(main->head_envar, "PATH");
	path = ft_strdup(envar->env_cont);
	char 	**path_split = ft_split(path,':');
	char *command = NULL;
	char **arg ;
	if(argc == 2)
		arg =ft_split(ft_strjoin(av[1], ":"),':');
	else if(argc == 3)
		arg= ft_split(ft_strjoin(ft_strjoin(av[1],":"),av[2]),':');
	else if(argc == 4)
		arg= ft_split(ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(av[1],":"),av[2]),":"),av[3]),':');
	while(path_split[i])
	{
		if(access(ft_strjoin((ft_strjoin(path_split[i],"/")),av[1]),F_OK) == 0)
		{
			command = ft_strjoin((ft_strjoin(path_split[i],"/")),av[1]);
		}
		i++;	
	}
	int err = execve(command,arg,NULL);
	i = 0;
	printf("%d '%s'\n",i,arg[i]);
	printf("%d '%s'\n",i,command);
	// while(arg[i])
	// {
	// 	printf("%d '%s'\n",i,arg[i]);
	// 	i++;
	// }
	// if(command == NULL)
	// 	printf("mini-chan: command not found: %s\n",av[1]);
	// else if(err == -1)
	// 	printf("mini-chan %s: %s: No such file or directory\n",av[1],av[2]);
}

char **arg_fill(char *arg)
{
	char **args = ft_split(arg,' ');
	return(args);
}

void close_fun(int num, int **fds)
{
	int i = 0;
	int j = 0;
	while(i < num - 1)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}

}

void ft_pipe(t_shell_chan *main,char *av[],int ac)
{
	t_mini_envar *envar;
	char	*path;
	envar = search_envar(main->head_envar, "PATH");
	path = ft_strdup(envar->env_cont);
	char 	**path_split = ft_split(path,':');

	char ***arg = (char ***)malloc(sizeof(char **) * ac);
	char **cmd = (char **)malloc(sizeof(char *)*ac);
	char **cmd_path = (char **)malloc(sizeof(char *)*ac);
	int i =0;
	int j = 1;
	int num_cmd = ac - 1;
	arg[ac] = NULL;
	cmd[ac] =NULL;
	while(j < ac)
	{
		arg[i] = ft_split(av[j],' ');
		i++;
		j++;
	}
	//todo fill commands
	i = 1;
	j = 0;
	while(i < ac)
	{
		cmd[j] = arg[j][0];
		i++;
		j++;
	}
	i = 0;
	j = 0;
	//todo check command paths and fill them in cmd_path
	while(cmd[i])
	{
		// printf("check path and command");
		j = 0;
		while(path_split[j])
		{
			if(access(ft_strjoin(ft_strjoin(path_split[j],"/"),cmd[i]),F_OK) == 0)
				cmd_path[i] = ft_strjoin(ft_strjoin(path_split[j],"/"),cmd[i]);
			j++;
		}
		if(j == 10 && cmd_path[i] == NULL)
		{
			printf("zsh: command not found: %s\n",cmd[i]);
			exit(127);
			break;
		}
		i++;
	}
	//?? **cmd_path(command path) && ***arg(cmd line)
	//todo init forks and pipe
	//------------------------------ ls | wc -l --------------------------------------------//
	/*
		1 PIPE 			->	end[2];
		2 CHILD PROCESS	->	fork(); fork();
	*/
	// int ends[2];
	// int s;
	// pid_t ch1;
	// pid_t ch2;
	// if(pipe(ends)<0)
	// 	printf("PIPE ERROR\n");
	// ch1 = fork();
	// if(ch1 == 0)
	// {
	// 	printf("here ch1");
	// 	close(ends[0]);
	// 	if(dup2(ends[1],STDOUT_FILENO) < 0)
	// 		perror("DUP2 : CH1");
	// 	close(ends[1]);
	// 	if(execve(cmd_path[0],arg[0], NULL) == -1)
	// 		perror("EXE : CH1");
	// }
	// 	ch2 = fork();
	// 	if(ch2 == 0)
	// 	{
	// 		printf("here ch2");
	// 		close(ends[1]);
	// 		if(dup2(ends[0],STDIN_FILENO) > 0)
	// 			perror("DUP2 : CH2 ");
	// 		close(ends[0]);
	// 		if(execve(cmd_path[1],arg[1],NULL) == -1)
	// 			perror("EXE : CH1");
	// 	}
	// waitpid(-1,&s,0);


	//------------------------------ cat exe.c | grep "DUP2" | wc -l --------------------------------------------//
	/*
		2 pipes
		3 childs 
			ch1 write -> pip1
			
			ch2 read -> pip1
			ch2 write -> pip2

			ch3 read -> pip2
		waitpid .. parent waits
	*/
// int end1[2];
	int end2[2];
	int s;
	j = 0;
	int **fds = malloc(sizeof(int *) * num_cmd - 1);
	i = 0;
	while(i < num_cmd -1)
	{
		
		// printf("FD %d\n",i);
		fds[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	// printf("cmd num %d\n",num_cmd);
	while(i < num_cmd -1)
	{
		j = 0;
		while(j < 2)
		{
			fds[i][j] = j;
			// printf("pipe %d[%d]\n",i,fds[i][j]);

			j++;
		}
		i++;
	}
	i = 0;
	while(i < num_cmd - 1) // 2	
	{
		if(pipe(fds[i]) < 0)
			perror("pipe");
		i++;
	}
	// printf("DONE\n");
	pid_t ch;
	i = 0;
	while(i < num_cmd) // 0 1 2 3
	{
		// printf("in loop\n");
		ch = fork();
		if ((i == 0) && ch == 0)
		{
			// printf("ch1 %d\n",i);
			if(dup2(fds[i][1],STDOUT_FILENO) < 0)
				perror("dup ch1");
			// j = 0;
			// while(j < num_cmd -1)
			// {
			// 	// printf("j %d\n",j);
			// 	close(fds[j][0]);
			// 	close(fds[j][1]);
			// 	j++;
			// }
			close_fun( num_cmd , fds);
			if(execve(cmd_path[i], arg[i],NULL) == -1)
				exit(127);
		}
		else if ((i == num_cmd -1) && ch == 0)
		{
			// printf("ch3 %d\n",i);
			if(dup2(fds[i -1][0],STDIN_FILENO) < 0)
				perror("dup ch3");
			close_fun( num_cmd , fds);
			// j = 0;
			// while(j < num_cmd -1)
			// {
			// 	// printf("j %d\n",j);
			// 	close(fds[j][0]);
			// 	close(fds[j][1]);
			// 	j++;
			// }
			if(execve(cmd_path[i],arg[i],NULL) == -1)
				exit(127);
		}
		else if (ch == 0)
		{
			// printf("mid ch %d\n",i);
			if(dup2(fds[i -1][0],STDIN_FILENO) < 0)
				perror("ch mid dup1"); // read from the pipe 
			if(dup2(fds[i][1],STDOUT_FILENO) < 0)
				perror("ch mid dup2"); // i + 1 to write in the next pipe
			close_fun( num_cmd , fds);
			// j = 0;
			// while(j < num_cmd -1)
			// {
			// 	// printf("j %d\n",j);
			// 	close(fds[j][0]);
			// 	close(fds[j][1]);
			// 	j++;
			// }
			if(execve(cmd_path[i],arg[i],NULL) == -1)
				exit(127);
		}
		i++;
	}
	// printf("DONE\n");
	waitpid(-1, &s, 0);
}
/*
gcc testing_double.c exe.c ../libft/libft.a ../src/mini_envar.c ../src/mini_envar_export.c ../src/mini_envar_tools.c ../src/mini_free.c ../src/mini_envar_export_tools.c ../src/mini_envar_unset.c
*/