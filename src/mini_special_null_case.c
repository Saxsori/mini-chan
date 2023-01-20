/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_special_null_case.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 02:26:30 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

void	skip_quote(t_null_parse *n_parse, char *line)
{
	while (++n_parse->i < ft_strlen(line))
	{
		if (line[n_parse->i] != '\t')
			return ;
		n_parse->counter++;
	}
}

int	is_there_null_arg(t_null_parse *n_parse, char *line)
{
	init_null_parse(n_parse);
	while (++n_parse->i < ft_strlen(line))
	{
		if (line[n_parse->i] == '\t')
		{
			if (n_parse->i == 0 || line[n_parse->i - 1] == ' ')
			{
				n_parse->counter++;
				skip_quote(n_parse, line);
				if (line[n_parse->i] == ' ' || line[n_parse->i] == '\0')
				{
					n_parse->num++;
					n_parse->tot_size += n_parse->counter;
				}
				n_parse->counter = 0;
			}
		}
	}
	return (n_parse->num);
}

int	skip_null_arg(t_null_parse *n_parse, char *line)
{
	int	i;

	i = n_parse->i;
	while (++i < ft_strlen(line))
	{
		if (line[i] != '\t')
			return (i);
		if (line[i + 1] == '\0')
		{
			return (i + 1);
		}
	}
	return (0);
}

/*
the condion 		
// if (line[n_parse->i] == '\t')
was above line 82
and that line was only
// (n_parse->i == 0 || line[n_parse->i - 1] == ' ')
*/
void	line_no_null_arg(t_null_parse *n_parse, char *line)
{
	n_parse->i = -1;
	n_parse->k = -1;
	n_parse->j = 0;
	while (++n_parse->i < ft_strlen(line))
	{
		if (line[n_parse->i] == '\t' && \
		(n_parse->i == 0 || line[n_parse->i - 1] == ' '))
		{
			n_parse->j = skip_null_arg(n_parse, line);
			if (n_parse->j > 0)
			{
				if (line[n_parse->j] == ' ' || line[n_parse->j] == '\0')
				{
					n_parse->new_line[++n_parse->k] = '\b';
					n_parse->i = n_parse->j;
					n_parse->j = 0;
				}
			}
		}
		if (++n_parse->k < n_parse->new_size)
			n_parse->new_line[n_parse->k] = line[n_parse->i];
		else
			break ;
	}
}

void	parse_special_null_arg(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		if (is_there_null_arg(&main->n_parse, main->first_split[i]))
		{
			main->n_parse.new_size = (ft_strlen(main->first_split[i]) \
				- main->n_parse.tot_size) + main->n_parse.num;
			main->n_parse.new_line = malloc(sizeof(char) * \
				(main->n_parse.new_size + 1));
			main->n_parse.new_line[main->n_parse.new_size] = '\0';
			line_no_null_arg(&main->n_parse, main->first_split[i]);
			free(main->first_split[i]);
			main->first_split[i] = ft_strdup(main->n_parse.new_line);
			free_ptr((void **)&main->n_parse.new_line);
		}
	}
}
