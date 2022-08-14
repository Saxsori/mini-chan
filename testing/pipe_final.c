/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_final.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 06:53:55 by dfurneau          #+#    #+#             */
/*   Updated: 2022/08/10 12:39:05 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
char	**path_finder(t_shell_chan *main, char **cmd, int ac)
{
	t_mini_envar	*envar;
	int				i;
	int				j;
	char			*path;
	char			**path_split;
	char			**cmd_path;

	envar = search_envar(main->head_envar, "PATH");
	path = ft_strdup(envar->env_cont);
	path_split = ft_split(path, ':');
	cmd_path = (char **)malloc(sizeof(char *) * ac);
	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (path_split[++j])
		{
			if (access(ft_strjoin(ft_strjoin(path_split[j], "/"), cmd[i]), F_OK) == 0)
			{
				cmd_path[i] = ft_strjoin(ft_strjoin(path_split[j], "/"), cmd[i]);
			}
		}
		if (j == 10 && cmd_path[i] == NULL)
		{
			printf("zsh: command not found: %s\n", cmd[i]);
			exit(127);
			break ;
		}
	}
	return (cmd_path);
}

void	init_fds(t_shell_chan *main, int num_cmd)
{
	int	i;
	int	j;

	main->fds = malloc(sizeof(int *) * num_cmd - 1);
	i = -1;
	while (++i < num_cmd - 1)
		main->fds[i] = (int *)malloc(sizeof(int) * 2);
	i = 0;
	while (i < num_cmd -1)
	{
		j = 0;
		while (j < 2)
		{
			main->fds[i][j] = j;
			j++;
		}
		i++;
	}
}

void	ft_dup_fds(t_shell_chan *main, int i, int num_cmd)
{
	if (i > 0)
	{
		if (dup2 (main->fds[i - 1][0], STDIN_FILENO) < 0)
			perror("testing dup2");
	}
	if (i < num_cmd - 1)
	{
		if (dup2 (main->fds[i][1], STDOUT_FILENO) < 0)
			perror("testing dup1");
	}
	if (i > 0)
	{
		if (close(main->fds[i - 1][0]) == -1)
			perror("1 close");
	}
	if (i < num_cmd - 1)
	{
		if (close(main->fds[i][1]) == -1)
			perror("2 close");
		if (close(main->fds[i][0]) == -1)
			perror("3 close");
	}
}

void	path_test(t_shell_chan *main, char *av[], int ac)
{
	char			**cmd_path;
	char			***arg;
	char			**cmd;
	int				i;
	int				j;
	int				num_cmd;
	pid_t			ch;
	int				status;

	arg = (char ***)malloc(sizeof(char **) * ac);
	cmd = (char **)malloc(sizeof(char *) * ac);
	i = -1;
	j = 0;
	num_cmd = ac -1;
	while (++j < ac)
		arg[++i] = ft_split(av[j], ' ');
	i = 0;
	j = -1;
	while (++i < ac)
	{
		++j;
		cmd[j] = arg[j][0];
	}
	cmd_path = path_finder(main, cmd, ac);
	init_fds(main, num_cmd);
	i = 0;
	while (i < num_cmd)
	{
		if (i < num_cmd -1)
		{
			if (pipe(main->fds[i]) < 0)
				perror("pipe add");
		}
		ch = fork();
		if (ch == 0)
		{
			if (i == 0)
			{
				ft_dup_fds(main, i, num_cmd);
				if (execve(cmd_path[i], arg[i], NULL) == -1)
				{
					perror("exe");
					exit(127);
				}
			}
			else if ((i == num_cmd -1) && ch == 0)
			{
				ft_dup_fds(main, i, num_cmd);
				if (execve(cmd_path[i], arg[i], NULL) == -1)
				{
					perror("exe");
					exit(127);
				}
			}
			else
			{
				ft_dup_fds(main, i, num_cmd);
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
				if (close(main->fds[i][1]) == -1)
					perror("first close\n");
			}
			if (i > 0)
			{
				if (close(main->fds[i - 1][0]) == -1)
					perror("testing sec close \n");
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