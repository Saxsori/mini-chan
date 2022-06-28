/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:05:04 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/28 13:00:42 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
#include <errno.h>
#include <string.h>
#include <sys/unistd.h>

void	mini_execute(t_mini_cmd *cmd)
{
	int				i;
	t_mini_envar	*envar;
	char			*path;
	char			**path_split;
	char			*err_command;
	envar = search_envar(cmd->main->head_envar, "PATH");
	path = ft_strdup(envar->env_cont);
	path_split = ft_split(path, ':');
	i = 0;
	err_command =ft_strdup(cmd->exe_tools.cmd_name);
	if(cmd->exe_tools.arg_num == 1)
		cmd->exe_tools.arguments = ft_split(ft_strjoin(cmd->exe_tools.cmd_name,":"),':'); //todo for a one command need '\0'
	while (path_split[i])
	{
		if(access(ft_strjoin((ft_strjoin(path_split[i], "/")), cmd->exe_tools.cmd_name),F_OK) == 0)
			cmd->exe_tools.cmd_name = ft_strjoin((ft_strjoin(path_split[i],"/")), cmd->exe_tools.cmd_name);
		i++;
	}
	
	i = 0;
	printf("nun %d\n", cmd->exe_tools.arg_num);
	printf("con %s\n", cmd->exe_tools.cmd_name);
	while (i < cmd->exe_tools.arg_num)
		printf("arg '%s'\n", cmd->exe_tools.arguments[i++]);
	if(access(cmd->exe_tools.cmd_name,F_OK) == -1)
		printf("mini-chan: %s: command not found\n",err_command);
	else if(execve(cmd->exe_tools.cmd_name, cmd->exe_tools.arguments, NULL) == -1 )
		strerror(errno);
}
