/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_get_parts.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 04:08:54 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/12 07:17:32 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"


/*
		// printf("%s\n", redir->arguments[redir->redir_tools.j]);
*/
void	get_redir_arg(t_mini_redir *redir, int op)
{
	// if (op == 1)
	// {
	// 	redir->redir_tools.i = 2;
	// 	redir->redir_tools.k = 1;
	// }
	// else
	// {
	// 	redir->redir_tools.i = 0;
	// 	redir->redir_tools.k = 0;
	// }
	// redir->redir_tools.j = 0;
	redir->arguments = (char **)malloc(sizeof(char *) * (redir->redir_tools.num_arg + 2));
	// // if (!redir->arguments[0])
	// // 	redir->arguments[0] = NULL;
	// // else
	redir->arguments[0] = ft_strdup(redir->command);
	redir->arguments[redir->redir_tools.num_arg + 1] = NULL;
	// while (++redir->redir_tools.i < redir->redir_tools.num_part)
	// {
	// 	if (redir->redir_tools.i == redir->redir_tools.r_pos[redir->redir_tools.k])
	// 	{
	// 		redir->redir_tools.i++;
	// 		redir->redir_tools.k++;
	// 	}
	// 	else
	// 		redir->arguments[++redir->redir_tools.j] = ft_strdup(redir->redir_tools.split[redir->redir_tools.i]);
	// }
	int	k;
	int	i;
	i = 0;
	if (op == 1)
	{
		redir->redir_tools.i = redir->redir_tools.pos_cmd;
		k = redir->redir_tools.k;
		printf ("i %d\n", redir->redir_tools.i);
		while (++redir->redir_tools.i < redir->redir_tools.num_part)
		{
			if (k < redir->redir_tools.num_redir)
			{
				if (redir->redir_tools.i == redir->redir_tools.r_pos[k])
				{
					// printf("i %d pos %d\n", redir->redir_tools.i, redir->redir_tools.r_pos[redir->redir_tools.k]);
					if (k + 1 < redir->redir_tools.num_redir)
						k++;
					redir->redir_tools.i++;
				}
				
			}
			else
			{
				printf ("arg\n");
				i++;
				if	(i == redir->redir_tools.num_arg + 1)
					break ;
				redir->arguments[i] = ft_strdup(redir->redir_tools.split[redir->redir_tools.i]);
			}
			// printf ("i %d pos %d k %d \n", redir->redir_tools.i, redir->redir_tools.r_pos[redir->redir_tools.k], redir->redir_tools.k);
		}
	}
	else
	{
		redir->redir_tools.i = 0;
		redir->redir_tools.k = 0;
		while (++redir->redir_tools.i < redir->redir_tools.num_part)
		{
			printf ("k %d limit for k %d\n", redir->redir_tools.k, redir->redir_tools.num_redir);
			if (redir->redir_tools.i == redir->redir_tools.r_pos[redir->redir_tools.k])
			{
				if (redir->redir_tools.k + 1 < redir->redir_tools.num_redir)
				{
					redir->redir_tools.k++;
				}
				redir->redir_tools.i++;
			}
			else
			{
				i++;
				if	(i == redir->redir_tools.num_arg + 1)
					break ;
				redir->arguments[i] = ft_strdup(redir->redir_tools.split[redir->redir_tools.i]);
			}
		}
	}
}

/*
*/
void	get_files(t_mini_redir *redir)
{
	int	i;
	// int	k;

	i = -1;
	while (++i < redir->redir_tools.num_file)
		redir->files[i] = ft_strdup(redir->redir_tools.split[redir->redir_tools.r_pos[i] + 1]);
	i = -1;
	while (++i < redir->redir_tools.num_redir)
	{
		// k = -1;
		printf("file -> (%s)\n", redir->files[i]);
		if (redir->files[i][0] == '\f')
			printf("(f)\n");
	}
		// printf("i %d - pos %d - file %s\n", i, redir->redir_tools.r_pos[i] + 1, redir->redir_tools.split[redir->redir_tools.r_pos[i] + 1]);
}

void	get_cmd(t_mini_redir *redir, int op)
{
	int	i;

	i = -1;
	if (op == 1)
	{
		printf ("syn 1\n");
		while (++i < redir->redir_tools.num_redir)
		{
			printf("redir pos %d\n", redir->redir_tools.r_pos[i]);
			if (i + 1 < redir->redir_tools.num_redir)
			{
				printf ("if %d != %d\n", redir->redir_tools.r_pos[i] + 2 , redir->redir_tools.r_pos[i + 1]);
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
		printf ("syn 2\n");
		if (!redir->redir_tools.split[0] || redir->redir_tools.split[0][0] == '\a')
			redir->command = NULL;
		else
			redir->command = ft_strdup(redir->redir_tools.split[0]);
	}
	printf("cmd - %s\n", redir->command);
}

/*
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
}
