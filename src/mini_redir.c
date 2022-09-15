/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 07:17:42 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/15 17:56:11 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
#include <stdio.h>
// #include <sys/_types/_pid_t.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void	redir_exe(t_mini_cmd *cmd)
{
	if (cmd->redir.command)
		path_finder(cmd);
	
	if ((access(cmd->cmd_path, X_OK) == -1) && \
	(access(cmd->cmd_path, F_OK) == 0))
	{
		errmsg(cmd->cmd_path, PER_ERR);
		exit(126);
	}
	if (execve(cmd->cmd_path, cmd->redir.arguments, NULL) == -1)
	{
		if (errno == 2 && cmd->tools.f_path == 1)
			errmsg(cmd->redir.command, NO_F_DIR);
		else
			errmsg(cmd->redir.command, NO_CMD);
		exit(127);
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

void	redir(t_mini_cmd *cmd)
{
	int		i;

	i = -1;
	cmd->redir.redir_tools.child = fork();
	if (cmd->redir.redir_tools.child == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		while (++i < cmd->redir.redir_tools.num_redir)
			redir_sign(cmd, i);
		if (!is_command(cmd->redir.command) && cmd->redir.command)
			redir_exe(cmd);
		else if (is_command(cmd->redir.command))
		{
			g_status = run_builtn(cmd);
			exit(g_status);
		}
		else if (!cmd->redir.command)
			exit(0);
	}
	else
		mini_wait(-1, cmd->redir.redir_tools.status);
}
