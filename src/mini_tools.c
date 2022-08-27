/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:48:11 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/26 14:34:37 by aaljaber         ###   ########.fr       */
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

int	no_cmd(char *line, int begin, int end)
{
	while (++begin < end)
	{
		if (line[begin] > 32 && line[begin] < 127)
			return (0);
	}
	return (1);
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

void	loop_init(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
		init_mini_cmd(&main->cmd_table[i], main);
}

/*
? 1- counting how many commands are there
? 2- depending on that counter do the malloc for the array of structures
? 3- if it was more than 1 then split them
?		else just take that one command and save it on first split
? 4- call function split command to split the parts and 
?	save each command on it's own structure

	BOO
todo	check || in mid of cmd line AND |     |  AND cmd|cmd||||cmd
		handel DONE ( cmd | cmd ||)
*/
void	first_cmd_split(t_shell_chan *main)
{
	cmd_counter(main);
	main->cmd_table = (t_mini_cmd *)malloc(main->cmd_num * sizeof(t_mini_cmd));
	loop_init(main);
	if (main->cmd_num > 1)
	{
		main->first_split = ft_split(main->cmd_line, '|');
		if (!main->first_split)
		{
			main->exit_status = 2;
			if (ft_strlen(main->cmd_line) == 1)
				printf (BRED"mini-chan🌸: syntax error near unexpected token `|'\n");
			else if (ft_strlen(main->cmd_line) > 1)
				printf (BRED"mini-chan🌸: syntax error near unexpected token `||'\n");
		}
		else if (!check_pipe(main->cmd_line))
		{
			main->exit_status = 2;
			printf (BRED"mini-chan🌸: syntax error near unexpected token `|'\n");
		}
	}
	else
	{
		main->first_split = (char **)malloc(sizeof (char *) * 2);
		main->first_split[0] = ft_strdup(main->cmd_line);
		main->first_split[1] = NULL;
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

/*
to replace the /v by space
*/
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
? if the split on | return NULL it means there is only |
! handle multiple pipe in the middle or one at the end
!  -> echo || or echo | or echo || cat
? check to replace the /v by spaces after split on spaces
*/
void	check_special_cases(t_shell_chan *main)
{
	int	i;

	// i = -1;
	// while (++i < main->cmd_num)
	// 	check_echo_arg(main->cmd_table[i]);
	i = -1;
	while (++i < main->cmd_num)
	{
		if (main->cmd_table[i].split == NULL)
		{
			printf (BRED"mini-chan🌸: syntax error near unexpected token `|'\n");
			main->exit_status = 2;
			//free
			return ;
		}
	}
	i = -1;
	while (++i < main->cmd_num)
		check_spaces(main->cmd_table[i].split);
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

	// main->cmd_table = (t_mini_cmd *)malloc(main->cmd_num * sizeof(t_mini_cmd));
	// i = -1;
	// while (++i < main->cmd_num)
	// 	init_mem_cmd(&main->cmd_table[i]);
	i = -1;
	while (++i < main->cmd_num && main->first_split[i] != NULL)
		main->cmd_table[i].split = ft_split(main->first_split[i], ' ');
	check_special_cases(main);
}
