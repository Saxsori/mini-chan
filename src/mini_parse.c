/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:17:28 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/15 11:14:50 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
? 1- save each command name in it's structure member
? 2- check if that command name is valid then return one 
?		to check then the other command parts
!! CHECK THIS WITH BOO if this needs edition 
!  depending on the other 
!  builtin commands since this will only work with the commands that
!  abrar did
	// while (++i < main->cmd_num)
	// 	printf("%s\n", main->cmd_table[i].name);
*/
void	command_name(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		if (main->cmd_table[i].split != NULL)
			main->cmd_table[i].name = ft_strdup(main->cmd_table[i].split[0]);
		else
			main->cmd_table[i].name = NULL;
	}
}

int	is_extst(char *line)
{
	if (!ft_strncmp(line, "$?", ft_strlen(line)))
		return (1);
	return (0);
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
