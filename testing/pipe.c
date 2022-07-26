/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:35:50 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/26 01:42:12 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
	struct
	- mini_exe_tools.cmd_name "ls" .. [execve]
	- mini_exe_tools.arg_num .. number of arguments
	- mini_exe_tools.arguments **char "ls" "-la" [execve]
	!need
	- *cmd_path = joint(path,cmd_name) [access]
	- **fds "allocate num_cmd -1" [dup2 & close]
	
	
	todo:status in struct ? in arr ..
	todo:child_id in arr ..
*/

void path_test(t_shell_chan *main,char *av[],int ac)
{
	t_mini_envar	*envar;//
	char			*path;//
	char			**path_split;//
	char			***arg;//
	char			**cmd; //
	char			**cmd_path;//
	int 			i;
	int				j;
	int				num_cmd;//
	int				**fds; //
	int				status;
	pid_t			ch;

	envar = search_envar(main->head_envar, "PATH");
	path = ft_strdup(envar->env_cont);
	path_split = ft_split(path, ':');
	arg = (char ***)malloc(sizeof(char **) * ac);
	cmd = (char **)malloc(sizeof(char *) * ac);
	cmd_path = (char **)malloc(sizeof(char *) * ac);
	num_cmd = ac - 1;
	arg[ac] = NULL;
	cmd[ac] = NULL;
	i = -1;
	j = 0;
	while (++j < ac)
		arg[++i] = ft_split(av[j], ' ');
	i = 0;
	j = -1;
	while (++i < ac)
	{
		++j;
		cmd[j] = arg[j][0];
	}
	
	// ************ finding the path
	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (path_split[++j])
		{
			if (access(ft_strjoin(ft_strjoin(path_split[j], "/"), cmd[i]), F_OK) == 0)
				cmd_path[i] = ft_strjoin(ft_strjoin(path_split[j], "/"), cmd[i]);
		}
		if (j == 10 && cmd_path[i] == NULL)
		{
			printf("zsh: command not found: %s\n", cmd[i]);
			exit(127);
			break ;
		}
	}
	// *************
	
	// !initialize the fd's array
	fds = malloc(sizeof(int *) * num_cmd - 1);
	i = -1;
	while (++i < num_cmd - 1)
		fds[i] = (int *)malloc(sizeof(int) * 2);
	i = 0;
	while (i < num_cmd -1)
	{
		j = 0;
		while (j < 2)
		{
			fds[i][j] = j;
			j++;
		}
		i++;
	}
	//! *******
	
	i = 0;
	while (i < num_cmd) 
	{
		if (i < num_cmd -1)
		{
			if (pipe(fds[i]) < 0)
				perror("pipe add");
		}
		ch = fork();
		if (ch == 0)
		{
			if (i == 0)
			{
				if (dup2(fds[i][1], STDOUT_FILENO) < 0)
					perror("dup ch1");
				if (close(fds[0][0]) == -1)
					perror("st 1");
				if (close(fds[0][1]) == -1)
					perror("sec 2");
				if (execve(cmd_path[i], arg[i], NULL) == -1)
				{
					perror("exe");		
					exit(127);
				}

			}
			else if ((i == num_cmd -1) && ch == 0)
			{
				if (dup2(fds[i -1][0], STDIN_FILENO) < 0)
					perror("dup ch last");
				if (close(fds[i -1][0]) == -1)
					perror("lst 1 close");
				if (execve(cmd_path[i], arg[i], NULL) == -1)
				{
					perror("exe");		
					exit(127);
				}

			}
			else
			{
				if (dup2(fds[i -1][0], STDIN_FILENO) < 0)
					perror("ch mid dup1");
				if (dup2(fds[i][1], STDOUT_FILENO) < 0)
					perror("ch mid dup2");
				if (close(fds[i-1][0]) == -1)
					perror("3close");
				if (close(fds[i][1]) == -1)
					perror("4close");
				if (close(fds[i][0]) == -1)
					perror("4close");
				if (execve(cmd_path[i], arg[i], NULL) == -1)
				{
					perror("exe");		
					exit(127);
				}
			}
		}
		else
		{
			if (i < num_cmd - 1)
			{
				if (close(fds[i][1]) == -1)
					perror("first close\n");
			}
			if (i > 0)
			{
				if (close(fds[i - 1][0]) == -1)
					perror("sec close \n");
			}
		}
			i++;

	}
	//******* wait childs 
	j = 0;
	while (j < 3)
	{
		waitpid(-1, &status, 0);
		j++;
	}
}
