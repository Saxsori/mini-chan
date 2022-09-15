/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_pre.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:27:27 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 07:54:35 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	last_redir(char *line, int i)
{
	int	k;

	k = i;
	while (++k < ft_strlen(line))
	{
		if (line[k] != '>' && line[k] != '<')
			return (k);
	}
	return (k);
}

/*

*/
int	is_redir_index(t_mini_cmd *cmd, int index)
{
	int	i;

	i = -1;
	while (++i < cmd->tools.p_redir.num_redir)
	{
		if (cmd->tools.p_redir.r_index[i] == index)
			return (1);
	}
	return (0);
}

/*
		// printf("%d here\n", main->cmd_table[i].tools.f_redir);
		// printf("here\n");

*/
int	redir_err_syn(t_shell_chan *main)
{
	int	i;
	int	k;

	i = -1;
	while (++i < main->cmd_num)
	{
		if (main->cmd_table[i].tools.f_redir)
		{
			k = -1;
			while (++k < main->cmd_table[i].tools.p_redir.num_redir)
			{
				if (main->cmd_table[i].tools.p_redir.r_valid[k] == 2)
					return (1);
			}
		}
	}
	return (0);
}

/*

to check if the redirextion is valid
? ->>> in loop
if the command has a redir
? 1- init the redir parsing structure
? 2- check if the redir is not btwn quote ">>"
? 3- check if there ie no more than two redir >>>
? 4- check if there is no opp redir ><

// k = -1;
// while (++k < main->cmd_table[i].tools.p_redir.num_redir)
// 	printf("not btwn quote %d\n", main->cmd_table[i].tools.p_redir.r_valid[k]);
// k = -1;
// while (++k < main->cmd_table[i].tools.p_redir.num_redir)
// 	printf("not more than tw %d\n", main->cmd_table[i].tools.p_redir.r_valid[k]);
// k = -1;
// while (++k < main->cmd_table[i].tools.p_redir.num_redir)
// 	printf("not opp redir %d\n", main->cmd_table[i].tools.p_redir.r_valid[k]);
*/
void	redir_valid(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		if (main->cmd_table[i].tools.f_redir)
		{
			init_loop_p_redir(&main->cmd_table[i], i);
			not_btwn_quote(&main->cmd_table[i], main->first_split[i]);
			not_more_than_two(&main->cmd_table[i], main->first_split[i]);
			not_opp_redir(&main->cmd_table[i], main->first_split[i]);
		}
	}
}

/*
prepare for redirection 
? 1- check if the redirection is valid
? 2- if there was any syntax error return 2
? 3- take the valid redirection
*/
int	pre_redir(t_shell_chan *main)
{
	redir_valid(main);
	if (redir_err_syn(main))
	{
		main->exit_status = 2;
		return (2);
	}
	take_v_redir(main);
	return (0);
}
