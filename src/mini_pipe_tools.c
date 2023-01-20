/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:00:35 by dfurneau          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

/*
TODO: should cover 
*/

/*
void	path_finder(t_mini_cmd *cmd)
{
	int		i;
	int		j;
	char	*command;

	j = 0;
	cmd->tools.f_path = 0;
	if (cmd->tools.y_redir)
		command = ft_strdup(cmd->redir.command);
	else
		command = ft_strdup(cmd->name);
	i = -1;
	while (command[++i])
	{
		if (command[i] == '/')
		{
			cmd->tools.f_path = 1;
			break ;
		}
	}
	if (cmd->tools.f_path == 0)
	{
		j = path_finder_split(cmd, j, command);
		i = -1;
		while (cmd->main->path[++i] && j != 1)
		{
			if (access(command, F_OK) == 0)
			{
				cmd->cmd_path = ft_strdup(command);
				free(command);
				break ;
			}
			else
				cmd->cmd_path = NULL;
		}
	}
}
*/

static void	search_path_loop(t_mini_cmd *cmd, char *command)
{
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	while (cmd->main->path_split[++i])
	{
		str1 = ft_strjoin(cmd->main->path_split[i], "/");
		str2 = ft_strjoin(str1, command);
		if (access(str2, F_OK) == 0)
		{
			cmd->cmd_path = ft_strdup(str2);
			free(str1);
			free(str2);
			cmd->tools.y_cmd = 1;
			break ;
		}
		else
		{
			cmd->tools.y_cmd = 0;
			free (str1);
			free (str2);
		}
	}
}

/*
took the loop to the search_path_loop function
*/
void	path_finder_split(t_mini_cmd *cmd, char *command)
{
	if (cmd->main->path)
		search_path_loop(cmd, command);
	else
	{
		cmd->cmd_path = NULL;
		cmd->tools.y_cmd = 0;
	}
}

void	init_fds(t_shell_chan *main)
{
	int	i;
	int	j;

	main->pipe_tools.fds = (int **)malloc(sizeof(int *) \
	* main->pipe_tools.p_num);
	i = -1;
	while (++i < main->pipe_tools.p_num)
		main->pipe_tools.fds[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < main->pipe_tools.p_num)
	{
		j = -1;
		while (++j < 2)
			main->pipe_tools.fds[i][j] = j;
	}
}

void	pipe_tools(t_shell_chan *main)
{
	int	i;

	i = -1;
	main->pipe_tools.child = malloc(sizeof(pid_t) * main->cmd_num);
	while (++i < main->cmd_num)
		main->pipe_tools.child[i] = -1;
	main->pipe_tools.p_num = main->cmd_num - 1;
	i = -1;
	while (++i < main->cmd_num)
		path_finder(&main->cmd_table[i]);
	init_fds(main);
}

void	ft_dup_fds(t_shell_chan *main, int i)
{
	if (i > 0)
	{
		if (dup2 (main->pipe_tools.fds[i - 1][0], STDIN_FILENO) < 0)
			perror(". dup2");
	}
	if (i < main->pipe_tools.p_num)
	{
		if (dup2 (main->pipe_tools.fds[i][1], STDOUT_FILENO) < 0)
			perror(". dup1");
	}
	if (i > 0)
	{
		if (close(main->pipe_tools.fds[i - 1][0]) == -1)
			perror(". 1 close");
	}
	if (i < main->pipe_tools.p_num)
	{
		if (close(main->pipe_tools.fds[i][1]) == -1)
			perror(". 2 close");
		if (close(main->pipe_tools.fds[i][0]) == -1)
			perror(". 3 close");
	}
}
