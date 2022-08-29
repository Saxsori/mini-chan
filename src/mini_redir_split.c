/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:36:26 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/28 17:56:15 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	check_redirline_syn(t_mini_redir *redir)
{
	int	i;

	i = -1;
	while (redir->redir_tools.split[++i] != NULL)
	{
		if (redir->redir_tools.split[i][0] == '\a')
		{
			if (redir->redir_tools.split[i + 1] == NULL)
			{
				redir->redir_tools.main->exit_status = 2;
				return (2);
			}
			else if (redir->redir_tools.split[i + 1][0] == '\a')
			{
				redir->redir_tools.main->exit_status = 2;
				return (2);
			}
		}
	}
	return (1);
}

/*
	// i = -1;
	// while (++i < redir->redir_tools.num_redir)
	// 	printf("pos -> %d\n", redir->redir_tools.r_pos[i]);
*/
void	get_redir_pos(t_mini_redir *redir)
{
	int	i;
	int	n;

	redir->redir_tools.num_file = redir->redir_tools.num_redir;
	redir->redir_tools.r_pos = (int *)malloc(sizeof(int) * redir->redir_tools.num_redir);
	redir->files = (char **)malloc(sizeof(char *) * (redir->redir_tools.num_file + 1));
	redir->files[redir->redir_tools.num_file] = NULL;
	i = -1;
	n = 0;
	while (redir->redir_tools.split[++i])
	{
		if (redir->redir_tools.split[i][0] == '\a')
			redir->redir_tools.r_pos[n++] = i;
	}
	redir->redir_tools.num_part = i;
}

/*

		// printf ("i %d - arg %d - pos %d k - %d\n",redir->redir_tools.i, redir->redir_tools.num_arg, redir->redir_tools.r_pos[redir->redir_tools.k], k);
*/
void	get_arg_num(t_mini_redir *redir, int op)
{
	if (op == 1)
	{
		redir->redir_tools.i = 2;
		redir->redir_tools.k = 1;
	}
	else
	{
		redir->redir_tools.i = 0;
		redir->redir_tools.k = 0;
	}
	while (++redir->redir_tools.i < redir->redir_tools.num_part)
	{
		if (redir->redir_tools.i == redir->redir_tools.r_pos[redir->redir_tools.k])
		{
			redir->redir_tools.i++;
			redir->redir_tools.k++;
		}
		else
			redir->redir_tools.num_arg++;
	}
}

void	replace_tabbing_spaces(char	**split)
{
	int	i;
	int	k;

	i = -1;
	while (split[++i])
	{
		k = -1;
		while (split[i][++k])
		{
			if (split[i][k] == '\v')
				split[i][k] = ' ';
		}
	}
}
/*

			// printf("cmd %s\n", main->cmd_table[i].redir.command);
			// printf("arg num %d\n", main->cmd_table[i].redir.redir_tools.num_arg);
*/
void	split_redir(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		if (main->cmd_table[i].tools.y_redir)
		{
			init_mini_redir(&main->cmd_table[i].redir, main, i);
			if (check_redirline_syn(&main->cmd_table[i].redir) == 2)
				break ;
			get_redir_pos(&main->cmd_table[i].redir);
			get_files(&main->cmd_table[i].redir);
			if (main->cmd_table[i].redir.redir_tools.split[0][0] == '\a')
				get_redir_part(&main->cmd_table[i].redir, 1);
			else
				get_redir_part(&main->cmd_table[i].redir, 2);
		}
	}
}
