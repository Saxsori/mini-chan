/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_get_parts.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfurneau <dfurneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 04:08:54 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/31 08:28:49 by dfurneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"


/*
		// printf("%s\n", redir->arguments[redir->redir_tools.j]);
*/
void	get_redir_arg(t_mini_redir *redir, int op)
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
	redir->redir_tools.j = 0;
	redir->arguments = (char **)malloc(sizeof(char *) * (redir->redir_tools.num_arg + 2));
	// if (!redir->arguments[0])
	// 	redir->arguments[0] = NULL;
	// else
	redir->arguments[0] = ft_strdup(redir->command);
	redir->arguments[redir->redir_tools.num_arg + 1] = NULL;
	while (++redir->redir_tools.i < redir->redir_tools.num_part)
	{
		if (redir->redir_tools.i == redir->redir_tools.r_pos[redir->redir_tools.k])
		{
			redir->redir_tools.i++;
			redir->redir_tools.k++;
		}
		else
			redir->arguments[++redir->redir_tools.j] = ft_strdup(redir->redir_tools.split[redir->redir_tools.i]);
	}
}

/*
	// i = -1;
	// while (++i < redir->redir_tools.num_redir)
	// 	printf("file -> %s\n", redir->files[i]);
		// printf("i %d - pos %d - file %s\n", i, redir->redir_tools.r_pos[i] + 1, redir->redir_tools.split[redir->redir_tools.r_pos[i] + 1]);
*/
void	get_files(t_mini_redir *redir)
{
	int	i;

	i = -1;
	while (++i < redir->redir_tools.num_file)
		redir->files[i] = ft_strdup(redir->redir_tools.split[redir->redir_tools.r_pos[i] + 1]);
}

void	get_cmd(t_mini_redir *redir, int op)
{
	if (op == 1)
	{
		if (!redir->redir_tools.split[2])
			redir->command = NULL;
		else
			redir->command = ft_strdup(redir->redir_tools.split[2]);
	}
	if (op == 2)
	{
		if (!redir->redir_tools.split[0])
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
	int	i;

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
	printf("heere\n");
	printf("cmd - %s\n", redir->command);
	i = -1;
	if (redir->arguments)
	{
		while (++i < redir->redir_tools.num_arg + 1)
			printf("arg - %s\n", redir->arguments[i]);
	}
	i = -1;
	if (redir->files)
	{
		while (++i < redir->redir_tools.num_file)
			printf("file - %s\n", redir->files[i]);
	}
}
