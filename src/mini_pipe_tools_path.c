/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe_tools_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:39:42 by balnahdi          #+#    #+#             */
/*   Updated: 2022/09/18 12:52:52 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	check_path_npipe(t_mini_cmd *cmd, char *command)
{
	int		i;

	i = -1;
	cmd->tools.f_path = 0;
	i = -1;
	while (command[++i])
	{
		if (command[i] == '/')
		{
			cmd->tools.f_path = 1;
			break ;
		}
	}
	return (cmd->tools.f_path);
}

char	*check_command(t_mini_cmd *cmd)
{
	char	*command;

	command = NULL;
	if (cmd->tools.y_redir)
	{
		if (cmd->redir.command)
			command = ft_strdup(cmd->redir.command);
	}
	else
	{
		if (cmd->name)
			command = ft_strdup(cmd->name);
	}
	return (command);
}

void	path_finder(t_mini_cmd *cmd)
{
	char	*command;

	command = check_command(cmd);
	if (!command)
	{
		cmd->tools.f_path = 1;
		cmd->cmd_path = NULL;
	}
	else
	{
		cmd->tools.f_path = check_path_npipe(cmd, command);
		if (cmd->tools.f_path == 1)
			cmd->cmd_path = ft_strdup(command);
	}
	if (cmd->tools.f_path == 0)
		path_finder_split(cmd, command);
	free (command);
}
	/*{
		j = path_finder_split(cmd, j, command);
		i = -1;
		while (cmd->main->path[++i] && j != 1)
		{
			if (access(command, F_OK) == 0)
			{
				// ft_putstr_fd(command, 2);
				// ft_putstr_fd("\n", 2);
				cmd->cmd_path = ft_strdup(command);
				// ft_putstr_fd(cmd->cmd_path, 2);
				// ft_putstr_fd("\n", 2);
				// cmd->tools.y_cmd = 1;
				break ;
			}
			else
			{
				cmd->cmd_path = NULL;
				cmd->tools.y_cmd = 0;
			}
		}
	}
	if (command)
		free(command);
	*/
