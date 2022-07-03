#include "../mini_chan.h"
#include <errno.h>
#include <stdio.h>
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
			break;
		}
		i++;
	}
	//?? **cmd_path(command path) && ***arg(cmd line)
	//todo init forks and pipe
	// int ends[num_cmd][2]; // 0 read 1 write
	// int st;
	// i = 0;
	// while(i < num_cmd)
	// {
	// 	if(pipe(ends[i])< 0)
	// 		perror("Error pipes ");
	// 	i++;
	// }
	// THE CREATION OF CHILD PROCESS AND EXE CHILD PROCESS SHOULD BE IN LOOP .. pid_t array
	// i = 0;
	// pid_t *child =(pid_t *)malloc(sizeof(pid_t) * num_cmd);
	// while(i < num_cmd)
	// {
	// 	child[i] = fork();
	// 	i++;
	// }
	// i = 0;
	// while(i < num_cmd)
	// {
	// 	if(child[i] == 0) // one dup2 if child == 0 || child == num_cmd -1 
	// 	{
	// 		if(i == 0)
	// 		{
	// 			// printf("child1 %d  cmd :%s arg:%s\n",i,cmd_path[i], arg[i][0]);
	// 			close(ends[i][0]);
	// 			if(dup2(ends[i][0],STDIN_FILENO) < 0)
	// 				perror("STD 1");
	// 			close(ends[i][1]);
	// 			execve(cmd_path[i],arg[i], NULL);
	// 		}
	// 		else if(i == num_cmd - 1)
	// 		{
	// 			printf("child last %d\n", i);
	// 		}
	// 		else
	// 		{
	// 			// printf("child2 %d\n",i);
	// 			close(ends[i][1]);
	// 			if(dup2(STDOUT_FILENO,STDIN_FILENO) < 0)
	// 				perror("STD OUT IN");
	// 			if(dup2(ends[i][0],STDOUT_FILENO) < 0)
	// 				perror("STD 2");
	// 			close(ends[i][0]);
	// 			execve(cmd_path[i],arg[i], NULL);
	// 		}
	// 	}
	// 	else
	// 	 	perror("child error ");
	// 	// waitpid(1,&st,0);
	// 	i++;
	// }
	// int ends[2];
	// pipe(ends);
	// pid_t child1 = fork();
	// int st;
	// if(child1 == 0)
	// {
	// 	close(ends[0]); // ? should i close all other ends for other child process ?
	// 	if(dup2(ends[1],STDOUT_FILENO) < 0)
	// 		perror("CH1 STDOUT");
	// 	close(ends[1]);
	// 	execve(cmd_path[0], arg[0] , NULL);
	// }


	// pid_t child2;
	// child2 = fork();
	// if(child2 == 0)
	// {
	// 	close(ends[1]); // ? should i close all other ends for other child process ?
	// 	if(dup2(ends[0],STDIN_FILENO) < 0)
	// 		perror("CH1 STDOUT");
	// 	close(ends[0]);
	// 	execve(cmd_path[1], arg[1] , NULL);
	// }
	// waitpid(1,&st,0);
	int ends[3][2];
	pipe(ends[0]);
	pipe(ends[1]);
	pid_t child1 = fork();
	int st;
	if(child1 == 0)
	{
		close(ends[0][1]); // ? should i close all other ends for other child process ?
		if(dup2(ends[0][0],STDIN_FILENO) < 0)
			perror("CH1 STDOUT");
		if(dup2(ends[1][1],STDOUT_FILENO) < 0)
				perror("CH1 STDOUT");		
		close(ends[0][0]);
		close(ends[0][1]);
		close(ends[1][0]);
		close(ends[1][1]);
		close(ends[2][0]);
		close(ends[2][1]);
		execve(cmd_path[0], arg[0] , NULL);
	}
	else{
		pid_t child2 = fork();
		if(child2 == 0)
		{
			// close(ends[][0]); // ? should i close all other ends for other child process ?
			// close
			if(dup2(ends[1][0],STDIN_FILENO) < 0)
				perror("CH2 STDOUT");
			if(dup2(ends[2][1],STDOUT_FILENO) < 0)
				perror("CH2 STDOUT");
			close(ends[0][0]);
			close(ends[0][1]);
			close(ends[1][0]);
			close(ends[1][1]);
			close(ends[2][0]);
			close(ends[2][1]);
			if(execve(cmd_path[1], arg[1] , NULL) == -1)
				perror("exe ");
		}
		else {
			pid_t child3;
			child3 = fork();
			if(child3 == 0)
			{
				// close(ends[1]); // ? should i close all other ends for other child process ?
				printf("here \n");
				if(dup2(ends[2][0],STDIN_FILENO) < 0)
					perror("CH3 STDOUT");
				close(ends[0][0]);
				close(ends[0][1]);
				close(ends[1][0]);
				close(ends[1][1]);
				close(ends[2][0]);
				close(ends[2][1]);
				if(execve(cmd_path[2], arg[2] , NULL) == -1)
					perror(" exe 3");
			}			
		
		
		}
	}	
	waitpid(1,&st,0);
	waitpid(1,&st,0);
	// waitpid(1,&st,0);
	// i = 0;
	// j = 0;
	// while(i < num_cmd)
	// {
	// 	j=0;
	// 	while(arg[i][j])
	// 	{
	// 		printf("%s\n",arg[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
	
	
}
/*
gcc testing_double.c exe.c ../libft/libft.a ../src/mini_envar.c ../src/mini_envar_export.c ../src/mini_envar_tools.c ../src/mini_free.c ../src/mini_envar_export_tools.c ../src/mini_envar_unset.c
*/