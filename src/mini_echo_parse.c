/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:05:27 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/09 03:11:13 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	is_echo(char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!cmd_strncmp(split[0], "echo", ft_strlen(split[0])))
	{
		squaredstr_free(split);
		return (1);
	}
	squaredstr_free(split);
	return (0);
}

void	skip_quote(t_mini_echo *e_parse, char *line)
{
	while (++e_parse->i < ft_strlen(line))
	{
		if (line[e_parse->i] != '\t')
			return ;
	}
}

int	count_null_arg(t_mini_echo *e_parse, char *line)
{
	int	num;

	e_parse->i = -1;
	num = 0;
	while (++e_parse->i < ft_strlen(line))
	{
		if (line[e_parse->i] == '\t')
		{
			if (line[e_parse->i - 1] == ' ')
			{
				skip_quote(e_parse, line);
				if (line[e_parse->i] == ' ')
					num++;
			}
		}
	}
	return (num);
}

/*
	// i = -1;
	// while (line[++i])
	// 	printf("(%c)\n", line[i]);
	 || \
					main->first_split[index][i + 2] == '\0'
*/
char	*line_no_null_arg(t_shell_chan *main, int index)
{
	int		i;
	char	*line;
	int		k;

	i = -1;
	k = 0;
	printf ("old size %d\n", ft_strlen(main->first_split[index]));
	line = (char *)malloc(sizeof(char) * (main->e_parse.new_size + 1));
	printf("new size %d\n", main->e_parse.new_size + 1);
	while (++i < ft_strlen(main->first_split[index]))
	{
		if (main->first_split[index][i] == '\t')
		{
			if (main->first_split[index][i + 1] == '\t')
			{
				if (main->first_split[index][i - 1] == ' ' && \
					(main->first_split[index][i + 2] == ' '))
				{
					line[k++] = '\v';
					i += 2;
				}
				else
					line[k++] = main->first_split[index][i];
			}
			else
				line[k++] = main->first_split[index][i];
		}
		else
			line[k++] = main->first_split[index][i];
	}
	line[k - 1] = '\0';
	//was line[k]
	printf("k %d\n", k);
	free (main->first_split[index]);
	return (line);
}

/*

			// printf ("yes echo\n");
			// printf("%d\n", main->e_parse.new_size);
			// printf("new size %d null num %d\n", \
			// main->e_parse.new_size, main->e_parse.null_num);
*/
void	parse_echo_case(t_shell_chan *main)
{
	int		i;
	// char	*line;
	i = -1;
	while (++i < main->cmd_num)
	{
		if (is_echo(main->first_split[i]))
		{
			main->e_parse.new_size = ft_strlen(main->first_split[i]);
			main->e_parse.null_num = count_null_arg(&main->e_parse, main->first_split[i]);
			printf("null arg %d\n", main->e_parse.null_num);
			// main->e_parse.new_size -= (main->e_parse.null_num);
			// if (main->e_parse.null_num > 0)
			// {
			// 	// line = line_no_null_arg(main, i);
			// 	// main->first_split[i] = ft_strdup(line);
			// 	main->first_split[i] = line_no_null_arg(main, i);
			// 	// free(line);
			// }
		}
	}
}
