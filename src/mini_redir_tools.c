/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:14:15 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/01 14:54:14 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

// void	redir_tools
	// redir_parse_tools(main);

int	is_redir(char *line)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '>' || line[i] == '<')
			return (1);
	}
	return (0);
}

void	check_redir(t_shell_chan *main, int i)
{
	if (is_redir(main->first_split[i]))
		main->cmd_table[i].tools.f_redir = 1;
	else
		main->cmd_table[i].tools.f_redir = 0;
}

int	is_more_redir(
void	count_redir(t_mini_cmd *cmd, int i)
{
	int	k;

	k = -1;
	cmd->tools.p_redir.num_redir = 0;
	while (++k < ft_strlen(cmd->main->first_split[i]))
	{
		if (cmd->main->first_split[i][k] == '>' || cmd->main->first_split[i][k] == '<')
		{
			k = is_more_redir(cmd->main->first_split[i], k);
			cmd->tools.p_redir.num_redir++;
		}
	}
}

void	redir_tools(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		check_redir(main, i);
		if (main->cmd_table[i].tools.f_redir)
		{
			count_redir(&main->cmd_table[i], i);
		}
	}
}