/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 07:17:42 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/04 03:14:39 by dfurneau         ###   ########.fr       */
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
	//todo path == null
	if (cmd->redir.command)
	{
		path_finder(cmd);
	}
	if (execve(cmd->cmd_path, cmd->redir.arguments, NULL) == -1)
	{
		write (2, "Command not found\n", 19);
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

	i = 0;
	// if (syntax_error_redir(cmd)
	cmd->redir.redir_tools.child = fork();
	if (cmd->redir.redir_tools.child == 0)
	{
		while (i < cmd->redir.redir_tools.num_redir)
		{
			redir_sign(cmd, i);
			i++;
		}
		if (!is_command(cmd->redir.command))
		{
			write(2, "9exe  here\n", 12);
			redir_exe(cmd);
		}
		else if (is_command(cmd->redir.command))
		{
			run_builtn(cmd);
			exit(0);
		}
	}
	else
	{
		waitpid(-1, &cmd->redir.redir_tools.status, 0);
		if (WIFEXITED(cmd->redir.redir_tools.status))
			g_status = WEXITSTATUS(cmd->redir.redir_tools.status);
		printf("-- >> EXIT CODE %d %d\n", \
		WEXITSTATUS(cmd->redir.redir_tools.status), g_status);
	}
}
