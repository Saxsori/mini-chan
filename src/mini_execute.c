/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 22:13:22 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/05 06:39:14 by dfurneau         ###   ########.fr       */
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

int	mini_execute(t_mini_cmd *cmd)
{
	int		i;
	int		status;
	pid_t	child;
	char	*str1;
	char	*str2;
	char	*str3;
	int		f = 0;
	i = 0;
	child = fork();
	while (cmd->exe_tools.cmd_name[i])
	{
		if(cmd->exe_tools.cmd_name[i] == '/')
		{
			f = 1;
			break;
		}
		i++;
	}
	if(f == 0)
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
	if (child == 0)
	{
		if (execve(cmd->exe_tools.cmd_name, cmd->exe_tools.arguments, \
		NULL) == -1)
		{
			if (errno == 2 && f == 1)
			{
				write(2, "mini-chan🌸: ", 16);
				write(2, cmd->exe_tools.arguments[0], \
				ft_strlen(cmd->exe_tools.arguments[0]));
				write(2, ": No such file or directory\n", \
				ft_strlen(": No such file or directory\n"));
			}
			else
			{
				write(2, "mini-chan🌸: ", 16);
				write(2, cmd->exe_tools.arguments[0], \
				ft_strlen(cmd->exe_tools.arguments[0]));
				write(2, ": command not found\n", 21);
			}
			ft_exit(cmd->main, 127);
		}
	}
	else
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	return (0);
}
