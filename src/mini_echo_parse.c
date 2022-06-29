/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:05:27 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/29 18:37:17 by aaljaber         ###   ########.fr       */
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

int	count_null_arg(char *line)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '\t')
		{
			if (line[i + 1] == '\t')
			{
				i++;
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
*/
char	*line_no_null_arg(t_shell_chan *main, int index)
{
	int		i;
	char	*line;
	int		k;

	i = -1;
	k = 0;
	line = (char *)malloc(sizeof(char) * (main->e_parse.new_size + 1));
	while (++i < ft_strlen(main->first_split[index]))
	{
		if (main->first_split[index][i] == '\t')
		{
			if (main->first_split[index][i + 1] == '\t')
			{
				if (main->first_split[index][i - 1] == ' ' && \
					(main->first_split[index][i + 2] == ' ' /*|| \
					main->first_split[index][i + 2] == '\0'*/))
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
	line[k] = '\0';
	free (main->first_split[index]);
	return (line);
}

void	parse_echo_case(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		if (is_echo(main->first_split[i]))
		{
			printf ("yes echo\n");
			main->e_parse.new_size = ft_strlen(main->first_split[i]);
			printf("%d\n", main->e_parse.new_size);
			main->e_parse.null_num = count_null_arg(main->first_split[i]);
			main->e_parse.new_size -= (main->e_parse.null_num);
			printf("new size %d null num %d\n", main->e_parse.new_size, main->e_parse.null_num);
			if (main->e_parse.null_num > 0)
				main->first_split[i] = line_no_null_arg(main, i);
		}
	}
}
