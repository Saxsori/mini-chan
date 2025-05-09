/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 07:17:42 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"
#include <stdio.h>
// #include <sys/_types/_pid_t.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void	redir_exe(t_mini_cmd *cmd)
{
	path_finder(cmd);
	if (cmd->redir.command[0] == '\0' && cmd->tools.y_cmd == 1)
		cmd->tools.y_cmd = 3;
	if (execve(cmd->cmd_path, cmd->redir.arguments, NULL) == -1)
	{
		if ((errno == 2 && cmd->tools.f_path == 1) || \
		(errno == 14 && cmd->tools.y_cmd != 3))
		{
			if (cmd->tools.y_cmd == 0 && cmd->main->no_path == 0)
				errmsg(cmd->redir.arguments[0], NO_CMD);
			else
				errmsg(cmd->redir.command, NO_F_DIR);
			exit(127);
		}
		else if (errno == 13 && cmd->tools.y_cmd == 1)
		{
			errmsg(cmd->redir.arguments[0], PER_ERR);
			exit(126);
		}
		else
		{
			errmsg(cmd->redir.arguments[0], NO_CMD);
			exit(127);
		}
	}
}

void	redir_sign(t_mini_cmd *cmd, int i)
{
	if (!ft_strncmp(cmd->redir.redir[i], ">", ft_strlen(">")))
		redir_in(cmd, i);
	else if (!ft_strncmp(cmd->redir.redir[i], "<", ft_strlen("<")))
		redir_out(cmd, i);
	else if (!ft_strncmp(cmd->redir.redir[i], ">>", ft_strlen(">>")))
		redir_append(cmd, i);
}

void	f_redir(t_mini_cmd *cmd)
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

void	redir(t_mini_cmd *cmd)
{
	int		i;

	i = -1;
	cmd->redir.redir_tools.child = fork();
	if (cmd->redir.redir_tools.child == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		while (++i < cmd->redir.redir_tools.num_redir)
		{
			redir_sign(cmd, i);
		}
		if (cmd->redir.command)
			f_redir(cmd);
		else
			exit(0);
	}
	else
		mini_wait(-1, cmd->redir.redir_tools.status);
}
