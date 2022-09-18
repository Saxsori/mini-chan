/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:29:41 by balnahdi          #+#    #+#             */
/*   Updated: 2022/09/18 15:36:34 by balnahdi         ###   ########.fr       */
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
	if (cmd->redir.command)
	{
		if (!is_command(cmd->redir.command))
		{
			redir_exe(cmd);
		}
		else if (is_command(cmd->redir.command))
		{
			g_status = run_builtn(cmd);
			exit(g_status);
		}
	}
	else
		exit (0);
}

void	pipe_exe_err(t_shell_chan *main, int i)
{
	if ((errno == 2 && main->cmd_table[i].tools.f_path == 1) || \
	(errno == 14 && main->cmd_table[i].tools.y_cmd != 3))
	{
		if (main->cmd_table[i].tools.y_cmd == 0 && main->no_path == 0)
			errmsg(main->cmd_table[i].exe_tools.arguments[0], NO_CMD);
		else
			errmsg(main->cmd_table[i].exe_tools.arguments[0], NO_F_DIR);
		exit(127);
	}
	else if (errno == 13 && main->cmd_table[i].tools.y_cmd == 1)
	{
		errmsg(main->cmd_table[i].exe_tools.arguments[0], PER_ERR);
		exit(126);
	}
	else
	{
		errmsg(main->cmd_table[i].exe_tools.arguments[0], NO_CMD);
		exit(127);
	}
}

void	pipe_exe(t_shell_chan *main, int i)
{
	ft_dup_fds(main, i);
	execute_tools(&main->cmd_table[i]);
	if (main->cmd_table[i].exe_tools.cmd_name[0] == '\0' && \
	main->cmd_table[i].tools.y_cmd == 1)
		main->cmd_table[i].tools.y_cmd = 3;
	if (execve(main->cmd_table[i].cmd_path, \
	main->cmd_table[i].exe_tools.arguments, NULL) == -1)
	{
		pipe_exe_err(main, i);
	}
}
/*
		if ((errno == 2 && main->cmd_table[i].tools.f_path == 1) || \
		(errno == 14 && main->cmd_table[i].tools.y_cmd != 3))
		{
			if (main->cmd_table[i].tools.y_cmd == 0 && main->no_path == 0)
				errmsg(main->cmd_table[i].exe_tools.arguments[0], NO_CMD);
			else
				errmsg(main->cmd_table[i].exe_tools.arguments[0], NO_F_DIR);
			exit(127);
		}
		else if (errno == 13 && main->cmd_table[i].tools.y_cmd == 1)
		{
			errmsg(main->cmd_table[i].exe_tools.arguments[0], PER_ERR);
			exit(126);
		}
		else
		{
			errmsg(main->cmd_table[i].exe_tools.arguments[0], NO_CMD);
			exit(127);
		}
	*/