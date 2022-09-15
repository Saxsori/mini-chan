/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_get_parts.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 04:08:54 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 10:02:27 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

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
