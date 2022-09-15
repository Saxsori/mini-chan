/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:19:49 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 18:34:20 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	pipe_redir(t_mini_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->redir.redir_tools.num_redir)
	{
		redir_sign(cmd, i);
		i++;
	}
	if (!is_command(cmd->redir.command))
		redir_exe(cmd);
	else if (is_command(cmd->redir.command))
	{
		g_status = run_builtn(cmd);
		exit(g_status);
	}
}

void	mini_exe_pipe(t_shell_chan *main, int i)
{
	if (main->cmd_table[i].tools.y_exe && !main->cmd_table[i].tools.y_redir)
	{
		ft_dup_fds(main, i);
		execute_tools(&main->cmd_table[i]);
		if (access(main->cmd_table[i].cmd_path, X_OK) == -1 && \
		(access(main->cmd_table[i].cmd_path, F_OK) == 0))
		{
			errmsg(main->cmd_table[i].cmd_path, PER_ERR);
			exit(126);
		}
		if (execve(main->cmd_table[i].cmd_path, \
		main->cmd_table[i].exe_tools.arguments, NULL) == -1)
		{
			if (main->cmd_table[i].tools.f_path == 1)
				errmsg(main->cmd_table[i].exe_tools.arguments[0], NO_F_DIR);
			else
				errmsg(main->cmd_table[i].exe_tools.arguments[0], NO_CMD);
			exit(127);
		}
	}
	else if (main->cmd_table[i].tools.y_redir)
		pipe_redir(&main->cmd_table[i]);
	else
	{
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