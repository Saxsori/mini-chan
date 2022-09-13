/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_get_parts.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 04:08:54 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/13 04:12:06 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"


/*
		// printf("%s\n", redir->arguments[redir->redir_tools.j]);
*/
void	get_redir_arg(t_mini_redir *redir, int op)
{
	int	k;
	int	i;

	redir->arguments = (char **)malloc(sizeof(char *) * (redir->redir_tools.num_arg + 2));
	redir->arguments[0] = ft_strdup(redir->command);
	redir->arguments[redir->redir_tools.num_arg + 1] = NULL;
	i = 0;
	if (op == 1)
	{
		redir->redir_tools.i = redir->redir_tools.pos_cmd;
		k = redir->redir_tools.k;
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
			}
			else
			{
				i++;
				if (i == redir->redir_tools.num_arg + 1)
					break ;
				redir->arguments[i] = ft_strdup(redir->redir_tools.split[redir->redir_tools.i]);
			}
		}
	}
	else
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
			{
				i++;
				if (redir->redir_tools.num_arg == 0 || i == redir->redir_tools.num_arg + 1)
					break ;
				redir->arguments[i] = ft_strdup(redir->redir_tools.split[redir->redir_tools.i]);
			}
		}
	}
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
		redir->files[i] = ft_strdup(redir->redir_tools.split[redir->redir_tools.r_pos[i] + 1]);
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
