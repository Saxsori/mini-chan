/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:19:49 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

void	mini_exe_pipe(t_shell_chan *main, int i)
{
	if (main->cmd_table[i].tools.y_exe && !main->cmd_table[i].tools.y_redir)
		pipe_exe(main, i);
	else if (main->cmd_table[i].tools.y_redir)
	{
		ft_dup_fds(main, i);
		pipe_redir(&main->cmd_table[i]);
	}
	else
	{
		if (cmd_strncmp(main->cmd_table[i].name, \
		"exit", ft_strlen(main->cmd_table[i].name)))
			ft_dup_fds(main, i);
		g_status = run_builtn(&main->cmd_table[i]);
		exit(g_status);
	}
}

void	split_pipe(t_shell_chan *main, int i)
{
	if (i == 0)
	{
		mini_exe_pipe(main, i);
	}
	else if ((i == main->pipe_tools.p_num) && main->pipe_tools.child == 0)
	{
		mini_exe_pipe(main, i);
	}
	else
		mini_exe_pipe(main, i);
}

void	close_fds(t_shell_chan *main, int i)
{
	if (i < main->pipe_tools.p_num)
	{
		if (close(main->pipe_tools.fds[i][1]) == -1)
			perror("close error\n");
	}
	if (i > 0)
	{
		if (close(main->pipe_tools.fds[i - 1][0]) == -1)
			perror("close error \n");
	}
}

void	ft_mini_pipe(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		if (i < main->pipe_tools.p_num)
		{
			if (pipe(main->pipe_tools.fds[i]) < 0)
				perror("pipe error");
		}
		main->pipe_tools.child[i] = fork();
		if (main->pipe_tools.child[i] == 0)
			split_pipe(main, i);
		else
			close_fds(main, i);
	}
	i = -1;
	while (++i < main->cmd_num)
		mini_wait(main->pipe_tools.child[i], main->pipe_tools.status);
}

/*

*/