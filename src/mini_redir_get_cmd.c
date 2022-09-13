/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_get_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 03:53:17 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/13 04:00:01 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"


void	choose_cmd(t_mini_redir *redir, int op, int i)
{
	if (op == 1)
	{
		redir->command = ft_strdup(redir->redir_tools.split[redir->redir_tools.r_pos[i] + 2]);
		redir->redir_tools.pos_cmd = redir->redir_tools.r_pos[i] + 2;
		redir->redir_tools.k = i + 1;
	}
}

/*
	// printf("cmd - %s\n", redir->command);
	? taking the command
	? the next position of the redir
	? 
*/
void	get_cmd(t_mini_redir *redir, int op)
{
	int	i;

	i = -1;
	if (op == 1)
	{
		while (++i < redir->redir_tools.num_redir)
		{
			if (i + 1 < redir->redir_tools.num_redir)
			{
				if (redir->redir_tools.r_pos[i] + 2 != redir->redir_tools.r_pos[i + 1])
				{
					redir->command = ft_strdup(redir->redir_tools.split[redir->redir_tools.r_pos[i] + 2]);
					redir->redir_tools.pos_cmd = redir->redir_tools.r_pos[i] + 2;
					redir->redir_tools.k = i + 1;
					break ;
				}
			}
			else if (i + 1 == redir->redir_tools.num_redir)
			{
				if (redir->redir_tools.r_pos[i] + 2 < redir->redir_tools.n_split)
				{
					redir->command = ft_strdup(redir->redir_tools.split[redir->redir_tools.r_pos[i] + 2]);
					redir->redir_tools.pos_cmd = redir->redir_tools.r_pos[i] + 2;
					redir->redir_tools.k = i + 1;
				}
				else
					redir->command = NULL;
			}
		}
	}
	if (op == 2)
	{
		if (!redir->redir_tools.split[0] || redir->redir_tools.split[0][0] == '\a')
			redir->command = NULL;
		else
			redir->command = ft_strdup(redir->redir_tools.split[0]);
	}
}
