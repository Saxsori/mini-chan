/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:05:04 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/29 09:09:54 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
#include <sys/wait.h>

/*
	// i = 0;
	// while (i < cmd->exe_tools.arg_num)
	// 	printf("arg '%s'\n", cmd->exe_tools.arguments[i++]);
*/

int	mini_execute(t_mini_cmd *cmd)
{
	int		i;
	int		status;
	pid_t	child;
	char	*str1;
	char	*str2;
	char	*str3;
	i = 0;
	child = fork();
	while (cmd->main->path_split[i])
	{
		str1 = (ft_strjoin(cmd->main->path_split[i], "/"));
		str2 = ft_strjoin(str1, cmd->exe_tools.cmd_name);
		if (access(str2, F_OK) == 0)
		{
			str3 = ft_strjoin(str1, cmd->exe_tools.cmd_name);
			free_ptr((void **)&cmd->exe_tools.cmd_name);
			cmd->exe_tools.cmd_name = ft_strdup(str3);
		}
		if(str1)
			free(str1);
		if(str2)
			free(str2);
			
		i++;
	}
	if (child == 0)
	{
		// if (access(cmd->exe_tools.cmd_name, F_OK) == -1)
		// 	printf("mini-chan🌸: %s: command not found\n", \//
		// 	cmd->exe_tools.err_command);
		if (execve(cmd->exe_tools.cmd_name, cmd->exe_tools.arguments, \
		NULL) == -1)
		{
			write(2, "mini-chan🌸: ", 16);
			write(2, cmd->exe_tools.arguments[0], ft_strlen(cmd->exe_tools.arguments[0]));
			write(2, ": command not found\n", 21);
			ft_exit(cmd->main, WIFEXITED(status));
			// exit(WIFEXITED(status));
			//WIFEXITED
		}
		
		
		//free all memory
		// exit(1);
	}
	else
	{
		waitpid(-1, &status, 0);
		// printf("status %d\n", WEXITSTATUS(status));
		// printf("exited %d\n", WEXITED);
	}
	
	// free(cmd->exe_tools.cmd_name);
	return (0);
}
