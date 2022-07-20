/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:05:04 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/20 10:49:35 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
	// i = 0;
	// while (i < cmd->exe_tools.arg_num)
	// 	printf("arg '%s'\n", cmd->exe_tools.arguments[i++]);
*/

void	mini_execute(t_mini_cmd *cmd)
{
	int		i;
	int		status;
	pid_t	child;

	i = 0;
	printf("here %d %s\n",cmd->exe_tools.arg_num, cmd->exe_tools.cmd_name);
	child = fork();
	while (cmd->main->path_split[i])
	{
		if (access(ft_strjoin((ft_strjoin(cmd->main->path_split[i], "/")), cmd->exe_tools.cmd_name),F_OK) == 0)
			cmd->exe_tools.cmd_name = ft_strjoin((ft_strjoin(cmd->main->path_split[i],"/")), cmd->exe_tools.cmd_name);
		i++;
	}
	if (child == 0)
	{
		// printf("\n");
		if (access(cmd->exe_tools.cmd_name, F_OK) == -1)
			printf("mini-chan🌸: %s: command not found\n", cmd->exe_tools.err_command);
		else if (execve(cmd->exe_tools.cmd_name, cmd->exe_tools.arguments, NULL) == -1)
			printf("mini-chan🌸: %s\n", strerror(errno));
	}
	else
		waitpid(-1, &status, 0);
}

// void	mini_exe_pipe(t_mini_cmd *cmd)
// {
	
// 	printf("sl7 %s\n",cmd->exe_tools.cmd_name);
// }

