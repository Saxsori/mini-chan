/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_special_null_case.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 02:26:30 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/09 05:59:26 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

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

void	line_no_null_arg(t_null_parse *n_parse, char *line)
{
	n_parse->i = -1;
	n_parse->k = -1;
	while (++n_parse->i < ft_strlen(line))
	{
		// printf("i %d , line (%c)\n", n_parse->i, line[n_parse->i]);
		if (line[n_parse->i] == '\t')
		{
			if (n_parse->i == 0 || line[n_parse->i - 1] == ' ')
			{
				skip_quote(n_parse, line);
				if (line[n_parse->i] == ' ' || line[n_parse->i] == '\0')
				{
					// printf("take dot\n");
					n_parse->new_line[++n_parse->k] = '\b';
				}
			}
		}
		// printf("k %d\n", n_parse->k);
		if (++n_parse->k < n_parse->new_size)
			n_parse->new_line[n_parse->k] = line[n_parse->i];
		else
		{
			// printf("break here (%c)\n", n_parse->new_line[n_parse->k]);
			break ;
		}
		// printf("k %d , new_line (%c)\n", n_parse->k, n_parse->new_line[n_parse->k]);
	}
}

void	parse_special_null_arg(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		printf("b4 ------> (%s)\n", main->first_split[i]);
		if (is_there_null_arg(&main->n_parse, main->first_split[i]))
		{
			printf("null num %d\n", main->n_parse.num);
			printf("tot_size %d\n", main->n_parse.tot_size);
			printf("line_size %d\n", ft_strlen(main->first_split[i]));
			printf("size without null quote %d\n", ft_strlen(main->first_split[i]) - main->n_parse.tot_size);
			main->n_parse.new_size = (ft_strlen(main->first_split[i]) - main->n_parse.tot_size) + main->n_parse.num;
			printf("new size %d\n", (ft_strlen(main->first_split[i]) - main->n_parse.tot_size) + main->n_parse.num);
			main->n_parse.new_line = malloc(sizeof(char) * (main->n_parse.new_size + 1));
			main->n_parse.new_line[main->n_parse.new_size] = '\0';
			line_no_null_arg(&main->n_parse, main->first_split[i]);
			printf("new_line (%s)\n", main->n_parse.new_line);
			free(main->first_split[i]);
			main->first_split[i] = ft_strdup(main->n_parse.new_line);
			free_ptr((void **)&main->n_parse.new_line);
		}
	}
}
