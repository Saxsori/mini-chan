/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 22:13:22 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/15 05:43:38 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
#include <sys/wait.h>

/*
	// i = 0;
	// while (i < cmd->exe_tools.arg_num)
	// 	printf("arg '%s'\n", cmd->exe_tools.arguments[i++]);


	todo 
		126 exit code use access(x_ok)
	todo
		/bin/lss not found should know the errno
*/

void	msg(int i)
{
	if (i == SIGQUIT)
		printf("Quit\n");
}

int	mini_execute(t_mini_cmd *cmd)
{
	int		i;
	int		status;
	char	*str1;
	char	*str2;
	char	*str3;

	cmd->tools.f_path = 0;
	cmd->tools.child = -1;
	i = 0;
	status = 0;
	cmd->tools.child = fork();
	while (cmd->exe_tools.cmd_name[i])
	{
		if (cmd->exe_tools.cmd_name[i] == '/')
		{
			cmd->tools.f_path = 1;
			break ;
		}
		i++;
	}
	if (cmd->tools.f_path == 0)
	{
		i = 0;
		while (cmd->main->path_split[i])
		{
			str1 = (ft_strjoin(cmd->main->path_split[i], "/"));
			str2 = ft_strjoin(str1, cmd->exe_tools.cmd_name);
			if (access(str2, F_OK) == 0)
			{
				str3 = ft_strjoin(str1, cmd->exe_tools.cmd_name);
				free_ptr((void **)&cmd->exe_tools.cmd_name);
				cmd->exe_tools.cmd_name = ft_strdup(str3);
				free (str3);
			}
			if (str1)
				free(str1);
			if (str2)
				free(str2);
			i++;
		}
	}
	if (cmd->tools.child == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (access(cmd->exe_tools.cmd_name, X_OK) == -1 && \
		(access(cmd->exe_tools.cmd_name, F_OK) == 0))
		{
			errmsg(cmd->exe_tools.cmd_name, PER_ERR);
			ft_exit(cmd->main, 126);
		}
		if (execve(cmd->exe_tools.cmd_name, cmd->exe_tools.arguments, \
		NULL) == -1)
		{
			if (errno == 2 && cmd->tools.f_path == 1)
				errmsg(cmd->exe_tools.arguments[0], PER_ERR);
			else
				errmsg(cmd->exe_tools.arguments[0], PER_ERR);
			ft_exit(cmd->main, 127);
		}
	}
	else
		mini_wait(-1, status);
	return (0);
}
