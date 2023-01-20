/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 22:13:22 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"
#include <sys/wait.h>

int	check_if_path(t_mini_cmd *cmd)
{
	int	i;

	cmd->tools.f_path = 0;
	i = -1;
	while (cmd->exe_tools.cmd_name[++i])
	{
		if (cmd->exe_tools.cmd_name[i] == '/')
		{
			cmd->tools.f_path = 1;
			break ;
		}
	}
	return (cmd->tools.f_path);
}

static void	search_path_loop(t_mini_cmd *cmd, int i)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = (ft_strjoin(cmd->main->path_split[i], "/"));
	str2 = ft_strjoin(str1, cmd->exe_tools.cmd_name);
	if (access(str2, F_OK) == 0)
	{
		str3 = ft_strjoin(str1, cmd->exe_tools.cmd_name);
		free_ptr((void **)&cmd->exe_tools.cmd_name);
		cmd->exe_tools.cmd_name = ft_strdup(str3);
		cmd->tools.y_cmd = 1;
		free_ptr((void **)&str1);
		free_ptr((void **)&str2);
		free_ptr((void **)&str3);
		cmd->tools.found_path = 1;
	}
	else
		cmd->tools.y_cmd = 0;
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

void	check_path(t_mini_cmd *cmd)
{
	int		i;

	cmd->tools.found_path = 0;
	i = -1;
	if (cmd->main->path)
	{
		while (cmd->main->path_split[++i])
		{
			search_path_loop(cmd, i);
			if (cmd->tools.found_path == 1)
				break ;
		}
	}
	else
		cmd->exe_tools.cmd_name = NULL;
}

void	mini_execute_split(t_mini_cmd *cmd)
{
	signal(SIGQUIT, SIG_DFL);
	if (cmd->null_cmd_line)
		ft_exit(cmd->main, 0);
	if (execve(cmd->exe_tools.cmd_name, cmd->exe_tools.arguments, \
	NULL) == -1)
	{	
		execute_err(cmd);
	}
}
/*
		if ((errno == 2 && cmd->tools.f_path == 1) || \
		(errno == 14 && cmd->tools.y_cmd != 3) || \
		(errno == 2 && cmd->tools.y_cmd == 1))
		{
			if (cmd->tools.y_cmd == 0 && cmd->main->no_path == 0)
				errmsg(cmd->redir.arguments[0], NO_CMD);
			else
				errmsg(cmd->exe_tools.arguments[0], NO_F_DIR);
			ft_exit(cmd->main, 127);
		}
		else if (errno == 13 && cmd->tools.y_cmd == 1)
		{
			errmsg(cmd->exe_tools.arguments[0], PER_ERR);
			ft_exit(cmd->main, 126);
		}
		else
		{
			errmsg(cmd->exe_tools.arguments[0], NO_CMD);
			ft_exit(cmd->main, 127);
		}
		*/

int	mini_execute(t_mini_cmd *cmd)
{
	int		status;

	cmd->tools.child = -1;
	status = 0;
	cmd->tools.f_path = check_if_path(cmd);
	if (cmd->tools.f_path == 0 && cmd->exe_tools.cmd_name[0] != '\0')
		check_path(cmd);
	else if (cmd->main->no_path == 0 && cmd->exe_tools.cmd_name[0] == '\0')
		cmd->tools.y_cmd = 3;
	else
		cmd->tools.y_cmd = 1;
	cmd->tools.child = fork();
	if (cmd->tools.child == 0)
		mini_execute_split(cmd);
	else
		mini_wait(-1, status);
	return (0);
}
