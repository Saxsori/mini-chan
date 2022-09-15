/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_quotes_split_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:27:10 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 12:32:28 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*

	// printf("envar num %d in index %d line %s\n", envar_num(main, i),
	//  i, main->first_split[i]);
*/
int	env_which_index(t_shell_chan *main, int index, int i)
{
	int	k;

	k = -1;
	while (++k < envar_num(main, i))
	{
		if (main->env_index[i][k] == index)
			return (k);
	}
	return (-1);
}

/*
line length with no quotes
? count the length of the string without the closed quote
*/
int	line_len(char *line)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (++i < ft_strlen(line))
	{
		if (line[i] != '\t')
			len++;
	}
	return (len);
}
