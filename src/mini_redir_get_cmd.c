/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_get_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 03:53:17 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

void	take_cmd(t_mini_redir *redir, int i)
{
	redir->command = \
		ft_strdup(redir->redir_tools.split[redir->redir_tools.r_pos[i] + 2]);
	redir->redir_tools.pos_cmd = redir->redir_tools.r_pos[i] + 2;
	redir->redir_tools.k = i + 1;
}

static void	cmd_syn_one(t_mini_redir *redir)
{
	int	i;

	i = -1;
	while (++i < redir->redir_tools.num_redir)
	{
		if (i + 1 < redir->redir_tools.num_redir)
		{
			if (redir->redir_tools.r_pos[i] + 2 \
								!= redir->redir_tools.r_pos[i + 1])
			{
				take_cmd(redir, i);
				break ;
			}
		}
		else if (i + 1 == redir->redir_tools.num_redir)
		{
			if (redir->redir_tools.r_pos[i] + 2 < redir->redir_tools.n_split)
				take_cmd(redir, i);
			else
				redir->command = NULL;
		}
	}
}

static void	cmd_syn_two(t_mini_redir *redir)
{
	if (!redir->redir_tools.split[0] || redir->redir_tools.split[0][0] == '\a')
		redir->command = NULL;
	else
		redir->command = ft_strdup(redir->redir_tools.split[0]);
}

/*
	// printf("cmd - %s\n", redir->command);
	? taking the command
	? the next position of the redir
	? 
*/
void	get_cmd(t_mini_redir *redir, int op)
{
	if (op == 1)
		cmd_syn_one(redir);
	if (op == 2)
		cmd_syn_two(redir);
}
