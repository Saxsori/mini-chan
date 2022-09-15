/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:55:57 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/15 11:07:31 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

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

void	check_null_arg(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->split)
	{
		while (cmd->split[++i])
		{
			printf("(%s) %d\n", cmd->split[i], i);
			if (cmd->split[i][0] == '\b')
			{
				free(cmd->split[i]);
				cmd->split[i] = malloc(sizeof(char));
				cmd->split[i][0] = '\0';
			}
		}
	}
	else
	{
		cmd->split = (char **)malloc(sizeof(char *) * 2);
		cmd->split[1] = NULL;
		cmd->split[0] = (char *)malloc(sizeof(char));
		cmd->split[0][0] = '\0';
	}
}

/*
? if the split on | return NULL it means there is only |
! handle multiple pipe in the middle or one at the end
!  -> echo || or echo | or echo || cat
? check to replace the /v by spaces after split on spaces
	// i = -1;
	// while (++i < main->cmd_num)
	// {
	// 	if (main->cmd_table[i].split == NULL)
	// 	{
	// 		printf (BRED"mini-chan🌸: syntax error near unexpected token `|'\n");
	// 		main->exit_status = 2;
	// 		//free
	// 		return ;
	// 	}
	// }
*/
void	check_special_cases(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		if (main->cmd_table[i].split)
			check_spaces(main->cmd_table[i].split);
	}
	i = -1;
	while (++i < main->cmd_num)
		check_null_arg(&main->cmd_table[i]);
}

/* 
? passing the command to each command structure 
? and at the same time splitting them from spaces 
? to seprate the command parts 
	// i = -1;
	// while (main->cmd_table[0].split[++i])
	// 	printf("%s\n", main->cmd_table[0].split[i]);
	// main->cmd_table = (t_mini_cmd *)malloc(main->cmd_num * sizeof(t_mini_cmd));
	// i = -1;
	// while (++i < main->cmd_num)
	// 	init_mem_cmd(&main->cmd_table[i]);
*/
void	split_command(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num && main->first_split[i] != NULL)
		main->cmd_table[i].split = ft_split(main->first_split[i], ' ');
	check_special_cases(main);
}
