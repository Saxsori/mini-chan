/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_take_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:24:27 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/31 22:17:12 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"


int	is_there_v_redir(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->tools.p_redir.num_redir)
	{
		if (cmd->tools.p_redir.r_valid[i] == -1)
			return (1);
	}
	return (0);
}

void	num_valid_redir(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (++i < cmd->tools.p_redir.num_redir)
	{
		if (cmd->tools.p_redir.r_valid[i] == -1)
			k++;
	}
	cmd->redir.redir_tools.num_redir = k;
}

void	change_null(t_mini_cmd *cmd, char *line)
{
	while (line[++cmd->tools.p_redir.i_temp])
	{
		if (line[cmd->tools.p_redir.i_temp] == 34 && \
		line[cmd->tools.p_redir.i_temp + 1] == 34)
		{
			printf("was here\n");
			if (line[cmd->tools.p_redir.i_temp - 1] == ' ' && \
			(line[cmd->tools.p_redir.i_temp + 2] == ' ' || line[cmd->tools.p_redir.i_temp + 2] == '\0'))
			{
				line[cmd->tools.p_redir.i_temp] = '\f';
				line[cmd->tools.p_redir.i_temp + 1] = ' ';
			}
		}
		else if (line[cmd->tools.p_redir.i_temp] == 39 && \
		line[cmd->tools.p_redir.i_temp + 1] == 39)
		{
			if (line[cmd->tools.p_redir.i_temp - 1] == ' ' && \
			(line[cmd->tools.p_redir.i_temp + 2] == ' '|| line[cmd->tools.p_redir.i_temp + 2] == '\0'))
			{
				line[cmd->tools.p_redir.i_temp] = '\f';
				line[cmd->tools.p_redir.i_temp + 1] = ' ';
			}
		}
	}
}

void	check_null_file(t_mini_cmd *cmd, char *line)
{
	cmd->tools.p_redir.i_temp = -1;
	while (++cmd->tools.p_redir.i_temp < ft_strlen(line))
	{
		if (line[cmd->tools.p_redir.i_temp] == '\a')
		{
			change_null(cmd, line);
		}
	}
}

void	take_v_redir(t_shell_chan *main)
{
	int	i;
	int	k;

	i = -1;
	while (++i < main->cmd_num)
	{
		if (is_there_v_redir(&main->cmd_table[i]))
		{
			main->cmd_table[i].tools.y_redir = 1;
			num_valid_redir(&main->cmd_table[i]);
			fill_redir_array(&main->cmd_table[i], main->first_split[i]);
			main->first_split[i] = replace_redir(main->first_split[i], &main->cmd_table[i]);
			printf("valid redir %s \n", main->first_split[i]);
			check_null_file(&main->cmd_table[i], main->first_split[i]);
			k = -1;
			while (++k < ft_strlen(main->first_split[i]))
			{
				if (main->first_split[i][k] == '\a')
					printf("(a)\n");
				else if (main->first_split[i][k] == '\f')
					printf("(f)\n");
				else
					printf("(%c)\n", main->first_split[i][k]);
			}
		}
	}
}