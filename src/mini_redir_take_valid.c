/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_take_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:24:27 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/31 03:39:14 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"


int	is_there_v_redir(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->tools.p_redir.num_redir)
	{
		if (cmd->tools.p_redir.r_valid[i] == -1)
			return (1);
	}
	return (0);
}

void	num_valid_redir(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (++i < cmd->tools.p_redir.num_redir)
	{
		if (cmd->tools.p_redir.r_valid[i] == -1)
			k++;
	}
	cmd->redir.redir_tools.num_redir = k;
}

void	take_v_redir(t_shell_chan *main)
{
	int	i;
	// int	k;

	i = -1;
	while (++i < main->cmd_num)
	{
		if (is_there_v_redir(&main->cmd_table[i]))
		{
			main->cmd_table[i].tools.y_redir = 1;
			num_valid_redir(&main->cmd_table[i]);
			fill_redir_array(&main->cmd_table[i], main->first_split[i]);
			main->first_split[i] = replace_redir(main->first_split[i], &main->cmd_table[i]);
			printf("vslid redir %s \n",  main->first_split[i]);
			// check_null_file(main->cmd_table[i]);
			
			// k = -1;
			// while (++k < ft_strlen(main->first_split[i]))
			// 	printf("(%c)\n", main->first_split[i][k]);
		}
	}
}