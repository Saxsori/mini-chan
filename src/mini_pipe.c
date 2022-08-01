/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:19:49 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/26 06:47:53 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
TODO: should cover 
*/
void	path_finder(t_mini_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	printf("cmd name %s\n", cmd->name);
	while (cmd->main->path_split[++i])
	{
		if (access(ft_strjoin(ft_strjoin(cmd->main->path_split[i], "/"), \
		cmd->name), F_OK) == 0)
		{
			cmd->cmd_path = ft_strjoin(ft_strjoin(cmd->main->path_split[i], \
			"/"), cmd->name);
			j = 1;
			break ;
		}
		else
			cmd->cmd_path = NULL;
	}
	i = -1;
	while (cmd->main->path[++i] && j != 1)
	{
		if (access(cmd->name, F_OK) == 0)
		{
			cmd->cmd_path = cmd->name;
			break ;
		}
		else
			cmd->cmd_path = NULL;
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

	main->pipe_tools.p_num = main->cmd_num - 1;
	i = -1;
	while (++i < main->cmd_num)
		path_finder(&main->cmd_table[i]);
	init_fds(main);
	i = -1;
	while (++i < main->cmd_num)
		printf("path_finder %s\n", main->cmd_table[i].cmd_path);
}

void	ft_dup_fds(t_shell_chan *main, int i)
{
	if (i > 0)
	{
		if (dup2 (main->pipe_tools.fds[i - 1][0], STDIN_FILENO) < 0)
			perror("dup2");
	}
	if (i < main->pipe_tools.p_num)
	{
		if (dup2 (main->pipe_tools.fds[i][1], STDOUT_FILENO) < 0)
			perror("dup1");
	}
	if (i > 0)
	{
		if (close(main->pipe_tools.fds[i - 1][0]) == -1)
			perror("1 close");
	}
	if (i < main->pipe_tools.p_num)
	{
		if (close(main->pipe_tools.fds[i][1]) == -1)
			perror("2 close");
		if (close(main->pipe_tools.fds[i][0]) == -1)
			perror("3 close");
	}
}
