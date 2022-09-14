/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_check_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 07:56:21 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 07:57:58 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
-> to check if this index is a redir pos 
-> cuz this array is to record all the rdir pos
			// printf ("i %d , index %d, i_redir %d\n", 
			//i , index ,cmd->tools.p_redir.r_index[i]);
*/
int	redir_pos(t_mini_cmd *cmd, int index)
{
	int	i;

	i = -1;
	while (++i < cmd->tools.p_redir.num_redir)
	{
		if (cmd->tools.p_redir.r_index[i] == index)
		{
			return (i);
		}
	}
	return (-1);
}

// void	redir_tools
	// redir_parse_tools(main);
int	is_redir(char *line)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '>' || line[i] == '<')
			return (1);
	}
	return (0);
}

void	check_redir(t_shell_chan *main, int i)
{
	if (is_redir(main->first_split[i]))
		main->cmd_table[i].tools.f_redir = 1;
	else
		main->cmd_table[i].tools.f_redir = 0;
}