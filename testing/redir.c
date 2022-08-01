/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:08:40 by dfurneau          #+#    #+#             */
/*   Updated: 2022/08/01 06:57:42 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../mini_chan.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void tst_redir(t_shell_chan *main,char *av[],int ac, int k)
{
	t_mini_envar	*envar;
	char			*path;
	char			**path_split;
	char			***arg;
	char			**cmd;
	char			**cmd_path;
	int				i;
	int				j;
	envar = search_envar(main->head_envar, "PATH");
	path = ft_strdup(envar->env_cont);
	path_split = ft_split(path, ':');
	arg = (char ***)malloc(sizeof(char **) * ac);
	cmd = (char **)malloc(sizeof(char *) * ac);
	cmd_path = (char **)malloc(sizeof(char *) * ac);
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
	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (path_split[++j])
		{
			if (access(ft_strjoin(ft_strjoin(path_split[j], "/"), \
				cmd[i]), F_OK) == 0)
				cmd_path[i] = ft_strjoin(ft_strjoin(path_split[j], \
				"/"), cmd[i]);
		}
		if (j == 10 && cmd_path[i] == NULL)
		{
			printf("zsh: command not found: %s\n", cmd[i]);
			exit(127);
			break ;
		}
	}
	execve(cmd_path[k], arg[k], NULL);
}


void tst_redir_main(t_shell_chan *main,char *av[],int ac)
{
	int i = 2;
	int k =0;
	int fd;
	int fd2;
	while(i < ac - 1)
	{
		if(av[i][0] == '>')
		{
			if(access(av[i + 1], F_OK) == -1)
				fd = open(av[i+1], O_WRONLY| O_TRUNC| O_CREAT, 0644);
			else
				fd = open(av[i+1], O_WRONLY| O_TRUNC| O_CREAT, 0644);
			dup2(fd,STDOUT_FILENO);
			close(fd);
		}
		else if(av[i][0] == '<')
		{
			if(access(av[i+1],F_OK) == 0)
				fd = open(av[i+1], O_RDONLY);
			else
			{
				printf("%s",av[i+1]);
				perror("mini-chan ");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if(av[i][0] == '}')
		{
			// printf("OUT HERE APPEND\n");
			if(access(av[i+1],F_OK) == -1)
				fd = open(av[i+1], O_WRONLY| O_APPEND| O_CREAT, 0644);
			else
				fd = open(av[i+1], O_WRONLY| O_APPEND| O_CREAT, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		
		i++;
	}
	tst_redir(main, av, ac,k);
}