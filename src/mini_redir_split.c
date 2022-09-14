/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:36:26 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 09:36:05 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

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
	redir->redir_tools.r_pos = (int *)malloc(sizeof(int) * \
								redir->redir_tools.num_redir);
	redir->files = (char **)malloc(sizeof(char *) * \
								(redir->redir_tools.num_file + 1));
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

static void	arg_syn_one(t_mini_redir *redir)
{
	int	k;

	redir->redir_tools.i = redir->redir_tools.pos_cmd;
	k = redir->redir_tools.k;
	printf("k %d num redir %d \n", k, redir->redir_tools.num_redir);
	while (++redir->redir_tools.i < redir->redir_tools.num_part)
	{
		if (k < redir->redir_tools.num_redir)
		{
			printf("i %d pos %d\n", redir->redir_tools.i, redir->redir_tools.r_pos[k]);
			if (redir->redir_tools.i == redir->redir_tools.r_pos[k])
			{
				if (k + 1 < redir->redir_tools.num_redir)
					k++;
				redir->redir_tools.i++;
			}
			else
				redir->redir_tools.num_arg++;
		}
		else
			redir->redir_tools.num_arg++;
	}
}

static void	arg_syn_two(t_mini_redir *redir)
{
	redir->redir_tools.i = 0;
	redir->redir_tools.k = 0;
	while (++redir->redir_tools.i < redir->redir_tools.num_part)
	{
		if (redir->redir_tools.i == redir->redir_tools.r_pos[redir->redir_tools.k])
		{
			if (redir->redir_tools.k + 1 < redir->redir_tools.num_redir)
				redir->redir_tools.k++;
			redir->redir_tools.i++;
		}
		else
			redir->redir_tools.num_arg++;
	}
}

/*

// printf ("i %d - arg %d - pos %d k - %d\n",\
	redir->redir_tools.i,\
	 redir->redir_tools.num_arg,\
	 redir->redir_tools.r_pos[redir->redir_tools.k], \
	 k);
// printf("i %d pos %d\n", redir->redir_tools.i, \
	redir->redir_tools.r_pos[redir->redir_tools.k]);
// printf ("i %d pos %d k %d \n", redir->redir_tools.i, \
		->redir_tools.r_pos[redir->redir_tools.k], \
		redir->redir_tools.k);
// printf ("k %d limit for k %d\n", redir->redir_tools.k, \
			redir->redir_tools.num_redir);
printf("arrrrg num %d\n", redir->redir_tools.num_arg);
*/
void	get_arg_num(t_mini_redir *redir, int op)
{
	if (op == 1)
		arg_syn_one(redir);
	else
		arg_syn_two(redir);
	printf ("arg num %d\n", redir->redir_tools.num_arg);
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
			{
				printf(BRED"mini-chan🌸: syntax error\n");
				break ;
			}
			get_redir_pos(&main->cmd_table[i].redir);
			get_files(&main->cmd_table[i].redir);
			if (main->cmd_table[i].redir.redir_tools.split[0][0] == '\a')
				get_redir_part(&main->cmd_table[i].redir, 1);
			else
				get_redir_part(&main->cmd_table[i].redir, 2);
		}
	}
}
