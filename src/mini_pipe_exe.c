/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:29:41 by balnahdi          #+#    #+#             */
/*   Updated: 2022/09/15 11:31:49 by balnahdi         ###   ########.fr       */
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

void	pipe_exe(t_shell_chan *main, int i)
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
