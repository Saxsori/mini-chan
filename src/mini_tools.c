/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:48:11 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/07 01:41:56 by aaljaber         ###   ########.fr       */
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

/*
? 1- counting how many commands are there
? 2- depending on that counter do the malloc for the array of structures
? 3- if it was more than 1 then split them
?		else just take that one command and save it on first split
? 4- call function split command to split the parts and 
?	save each command on it's own structure
*/
void	first_cmd_split(t_shell_chan *main)
{
	cmd_counter(main);
	main->cmd_table = (t_mini_cmd *)malloc(main->cmd_num * sizeof(t_mini_cmd));
	if (main->cmd_num > 1)
		main->first_split = ft_split(main->cmd_line, '|');
	else
	{
		main->first_split = (char **)malloc(sizeof (char *));
		main->first_split[0] = ft_strdup(main->cmd_line);
	}
}

/*
? to calculate how many strings in 2d array
! check if u need to change it to calc any other 2d array 
!	of any types	
*/
int	twstrlen(char	**tw_str)
{
	int	i;

	i = 0;
	while (tw_str[i])
		i++;
	return (i);
}

void	check_spaces(char **line)
{
	int	i;
	int	k;

	i = -1;
	while (line[++i])
	{
		k = -1;
		while (line[i][++k])
		{
			if (line[i][k] == '\v')
				line[i][k] = ' ';
		}
	}
}

/* 
? passing the command to each command structure 
? and at the same time splitting them from spaces 
? to seprate the command parts 
	// i = -1;
	// while (main->cmd_table[0].split[++i])
	// 	printf("%s\n", main->cmd_table[0].split[i]);
*/
void	split_command(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num && main->first_split[i] != NULL)
		main->cmd_table[i].split = ft_split(main->first_split[i], ' ');
	i = -1;
	while (++i < main->cmd_num)
		check_spaces(main->cmd_table[i].split);
}

int	check_cmd_line(char *line)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(line))
	{
		if (line[i] > 32)
			return (1);
	}
	return (0);
}
