/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipe_pre.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:38:31 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/08 20:36:36 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	cmd_counter(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(main->cmd_line))
	{
		if (main->cmd_line[i] == '|')
			main->cmd_num++;
	}
	main->cmd_num++;
}

void	remove_invalid_pipe(t_shell_chan *main, char *line, int index)
{
	while (++index < main->q_pars.end)
	{
		if (line[index] == line[main->q_pars.begin])
		{
			main->q_pars.begin = index;
			break ;
		}
		else if (line[index] == '|')
			line[index] = '\v';
	}
}

void	check_valid_pipe(t_shell_chan *main)
{
	init_mini_quotes(main, main->cmd_line);
	while (++main->q_pars.begin < main->q_pars.end)
	{
		if (main->cmd_line[main->q_pars.begin] == 34 || main->cmd_line[main->q_pars.begin] == 39)
			remove_invalid_pipe(main, main->cmd_line, main->q_pars.begin);
	}
}

int	check_pipe(char *line)
{
	int	i;
	int	begin;

	i = -1;
	begin = -1;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '|')
		{
			if (no_cmd(line, begin, i))
				return (0);
			begin = i;
		}
		if (line[i + 1] == '\0')
		{
			if (line[begin] == '|')
			{
				if (no_cmd(line, begin, i))
					return (0);
			}
		}
	}
	return (1);
}

void	return_invalid_pipe(t_shell_chan *main)
{
	int	i;
	int	k;

	i = -1;
	while (main->first_split[++i])
	{
		k = -1;
		while (main->first_split[i][++k])
		{
			if (main->first_split[i][k] == '\v')
				main->first_split[i][k] = '|';
		}
		printf("new %s\n", main->first_split[i]);
	}
}
