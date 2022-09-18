/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:05:00 by balnahdi          #+#    #+#             */
/*   Updated: 2022/09/18 13:07:38 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/****************************  PARSE_REDIR  ***********************************/
/*
? redir tools
*/
void	init_predir(t_redir_parse *p_redir)
{
	p_redir->num_redir = 0;
	p_redir->begin = -1;
	p_redir->end = -1;
	p_redir->r_index = NULL;
	p_redir->r_valid = NULL;
}

/*
? redir tools
*/
void	init_predir_arrays(t_redir_parse *p_redir)
{
	int	i;

	i = -1;
	p_redir->r_index = (int *)malloc(sizeof(int) * p_redir->num_redir);
	p_redir->r_valid = (int *)malloc(sizeof(int) * p_redir->num_redir);
	p_redir->i_temp = 0;
	while (++i < p_redir->num_redir)
	{
		p_redir->r_index[i] = -1;
		p_redir->r_valid[i] = -1;
	}
}

/*
? redir pre
*/
void	init_loop_p_redir(t_mini_cmd *cmd, int i)
{
	cmd->tools.p_redir.begin = -1;
	cmd->tools.p_redir.end = ft_strlen(cmd->main->first_split[i]);
}

void	init_mini_redir_tools(t_mini_redir *redir)
{
	int	i;

	i = -1;
	while (redir->redir_tools.split[++i])
	{
		if (redir->redir_tools.split[i][0] == '\b')
		{
			free(redir->redir_tools.split[i]);
			redir->redir_tools.split[i] = malloc(sizeof(char));
			redir->redir_tools.split[i][0] = '\0';
		}
	}
	redir->redir_tools.n_split = i;
	replace_tabbing_spaces(redir->redir_tools.split);
}

/*
? split redir
		// printf("redir split (%s)\n", redir->redir_tools.split[i]);
	// printf("n_split %d\n", redir->redir_tools.n_split);
*/
void	init_mini_redir(t_mini_redir *redir, t_shell_chan *main, int i)
{
	redir->arguments = NULL;
	redir->command = NULL;
	redir->files = NULL;
	redir->redir_tools.main = main;
	redir->redir_tools.pos_cmd = -1;
	redir->redir_tools.n_split = -1;
	redir->redir_tools.num_arg = 0;
	redir->redir_tools.num_file = 0;
	redir->redir_tools.parse_err = 0;
	redir->redir_tools.num_part = 0;
	redir->redir_tools.i = -1;
	redir->redir_tools.j = -1;
	redir->redir_tools.k = -1;
	redir->redir_tools.r_pos = NULL;
	redir->redir_tools.child = -1;
	redir->redir_tools.status = 0;
	redir->redir_tools.ld = 0;
	redir->redir_tools.fd = NULL;
	redir->redir_tools.split = ft_split(main->first_split[i], ' ');
	init_mini_redir_tools(redir);
}
/****************************  PARSE_REDIR  ***********************************/
