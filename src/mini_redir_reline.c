/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_reline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 03:03:19 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

int	isvla_redir(t_mini_cmd *cmd, int index)
{
	int	i;

	i = -1;
	while (++i < cmd->tools.p_redir.num_redir)
	{
		if (cmd->tools.p_redir.r_index[i] == index)
		{
			if (cmd->tools.p_redir.r_valid[i] == -1)
				return (1);
		}
	}
	return (0);
}

/*
	// char	*new;
	// int		len;
	// int		i;
	// int		k;
	// int		end;
*/
char	*replace_redir(char	*line, t_mini_cmd *cmd)
{
	cmd->redir.redir_tools.len = ft_strlen(line) + \
						(cmd->redir.redir_tools.num_redir * 2);
	cmd->redir.redir_tools.new = (char *)malloc(sizeof(char) * \
						(cmd->redir.redir_tools.len + 1));
	cmd->redir.redir_tools.i = -1;
	cmd->redir.redir_tools.k = 0;
	while (++cmd->redir.redir_tools.i < ft_strlen(line))
	{
		if (isvla_redir(cmd, cmd->redir.redir_tools.i))
		{
			cmd->redir.redir_tools.new[cmd->redir.redir_tools.k++] = ' ';
			cmd->redir.redir_tools.end = is_more_redir(line, \
										cmd->redir.redir_tools.i);
			while (cmd->redir.redir_tools.i++ < cmd->redir.redir_tools.end)
				cmd->redir.redir_tools.new[cmd->redir.redir_tools.k++] = '\a';
			cmd->redir.redir_tools.i -= 2;
			cmd->redir.redir_tools.new[cmd->redir.redir_tools.k++] = ' ';
		}
		else
			cmd->redir.redir_tools.new[cmd->redir.redir_tools.k++] \
									= line[cmd->redir.redir_tools.i];
	}
	cmd->redir.redir_tools.new[cmd->redir.redir_tools.k] = '\0';
	free(line);
	return (cmd->redir.redir_tools.new);
}
