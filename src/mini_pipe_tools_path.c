/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe_tools_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:39:42 by balnahdi          #+#    #+#             */
/*   Updated: 2022/09/16 15:06:01 by aaljaber         ###   ########.fr       */
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
	int		i;
	int		j;
	char	*command;

	j = 0;
	command = check_command(cmd);
	if (!command)
	{
		cmd->tools.f_path = 1;
		cmd->cmd_path = NULL;
	}
	else
		cmd->tools.f_path = check_path_npipe(cmd, command);
	if (cmd->tools.f_path == 0)
	{
		j = path_finder_split(cmd, j, command);
		i = -1;
		while (cmd->main->path[++i] && j != 1)
		{
			if (access(command, F_OK) == 0)
			{
				cmd->cmd_path = ft_strdup(command);
				break ;
			}
			else
				cmd->cmd_path = NULL;
		}
	}
	if (command)
		free(command);
}
