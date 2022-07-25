/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:19:49 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/25 22:06:57 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
TODO: should cover 
*/
void	path_finder(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->main->path_split[++i])
	{
		if (access(ft_strjoin(ft_strjoin(cmd->main->path_split[i], "/"), cmd->name), F_OK) == 0)
			cmd->cmd_path = ft_strjoin(ft_strjoin(cmd->main->path_split[i], "/"), cmd->name);
	}
}

void	pipe_tools(t_shell_chan *main)
{
	int	i;

	main->pipe_tools.p_num = main->cmd_num - 1;
	i = 0;
	while (i < main->cmd_num)
		path_finder(&main->cmd_table[i]);
}