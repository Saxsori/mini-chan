/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_get_parts.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 04:08:54 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 09:59:04 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

static void	get_synone_arg(t_mini_redir *redir, int op)
{
	if (op == 1)
	{
		redir->redir_tools.v++;
		redir->arguments[redir->redir_tools.v] = \
				ft_strdup(redir->redir_tools.split[redir->redir_tools.i]);	
	}
	else
	{
		redir->arguments[redir->redir_tools.v] = \
				ft_strdup(redir->redir_tools.split[redir->redir_tools.i]);	
	}
}	

static void	arg_syn_one(t_mini_redir *redir, int k)
{
	redir->redir_tools.i = redir->redir_tools.pos_cmd;
	k = redir->redir_tools.k;
	redir->redir_tools.v = 0;
	while (++redir->redir_tools.i < redir->redir_tools.num_part)
	{
		if (k < redir->redir_tools.num_redir)
		{
			if (redir->redir_tools.i == redir->redir_tools.r_pos[k])
			{
				if (k + 1 < redir->redir_tools.num_redir)
					k++;
				redir->redir_tools.i++;
			}
			else
				get_synone_arg(redir, 1);
		}
		else
		{
			redir->redir_tools.v++;
			if (redir->redir_tools.v == redir->redir_tools.num_arg + 1)
				break ;
			get_synone_arg(redir, 2);
		}
	}
}

static void	arg_syn_two(t_mini_redir *redir, int i)
{
	redir->redir_tools.i = 0;
	redir->redir_tools.k = 0;
	while (++redir->redir_tools.i < redir->redir_tools.num_part)
	{
		if (redir->redir_tools.i == \
					redir->redir_tools.r_pos[redir->redir_tools.k])
		{
			if (redir->redir_tools.k + 1 < redir->redir_tools.num_redir)
				redir->redir_tools.k++;
			redir->redir_tools.i++;
		}
		else
		{
			i++;
			if (redir->redir_tools.num_arg == 0 \
				|| i == redir->redir_tools.num_arg + 1)
				break ;
			redir->arguments[i] = \
				ft_strdup(redir->redir_tools.split[redir->redir_tools.i]);
		}
	}
}

/*
		// printf("%s\n", redir->arguments[redir->redir_tools.j]);
*/
void	get_redir_arg(t_mini_redir *redir, int op)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	redir->arguments = (char **)malloc(sizeof(char *) * \
		(redir->redir_tools.num_arg + 2));
	redir->arguments[0] = ft_strdup(redir->command);
	redir->arguments[redir->redir_tools.num_arg + 1] = NULL;
	if (op == 1)
		arg_syn_one(redir, k);
	else
		arg_syn_two(redir, i);
}

/*

	// i = -1;
	// while (++i < redir->redir_tools.num_redir)
	// {
	// 	// k = -1;
	// 	printf("file -> (%s)\n", redir->files[i]);
	// 	if (redir->files[i][0] == '\f')
	// 		printf("(f)\n");
	// }
*/
void	get_files(t_mini_redir *redir)
{
	int	i;

	i = -1;
	while (++i < redir->redir_tools.num_file)
		redir->files[i] = \
		ft_strdup(redir->redir_tools.split[redir->redir_tools.r_pos[i] + 1]);
}

/*
	
	// int	i;
	// printf("heere\n");
	// printf("cmd - %s\n", redir->command);
	// i = -1;
	// if (redir->arguments)
	// {
	// 	while (++i < redir->redir_tools.num_arg + 1)
	// 		printf("arg - %s\n", redir->arguments[i]);
	// }
	// i = -1;
	// if (redir->files)
	// {
	// 	while (++i < redir->redir_tools.num_file)
	// 		printf("file - %s\n", redir->files[i]);
	// }
*/
void	get_redir_part(t_mini_redir *redir, int op)
{
	get_cmd(redir, op);
	if (redir->command)
	{
		get_arg_num(redir, op);
		get_redir_arg(redir, op);
	}
	else
	{
		redir->redir_tools.num_arg = 0;
		redir->arguments = NULL;
	}
}
