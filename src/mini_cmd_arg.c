/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:06:52 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/25 20:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
? 1- calc how many parts (string) in the 
?	cmd->split (splitting parts from spaces)
? 2- to know how many arguments = 
?	num of parts - the index from where the arg is starting
? 3- malloc the 2d array of arguments depending on how many numbers of args
? 4- malloc each array depending on the size of each array using strlen
?	NOTE that where taking the size of ech array from the parts that we split in
?	cmd->split .. so it shpuld start from the index from where arg is begin
*/
void	pre_arg(t_mini_cmd *cmd)
{
	cmd->tools.p_num = twstrlen(cmd->split);
	cmd->tools.arg_num = cmd->tools.p_num - cmd->tools.arg_index;
	cmd->arguments = (char **)malloc((cmd->tools.arg_num + 1) * sizeof(char *));
	cmd->arguments[cmd->tools.arg_num] = NULL;
}

/*
? 1- prepare the cmd->arguments by calculating 
?	how many arg and malloc depending on that
? 2- fill the arg's 2d array
?	getting the arguments from the split starting
?	drom where the args is starting using arg_index
! check when it's only one arg 
	i = -1;
	while (++i < cmd->tools.arg_num)
		printf ("%s\n", cmd->arguments[i]);
*/
void	get_arg(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	pre_arg(cmd);
	k = cmd->tools.arg_index;
	i = -1;
	while (++i < cmd->tools.arg_num)
		cmd->arguments[i] = ft_strdup(cmd->split[k++]);
}

/*
if it does have '-' then it's opt not arg so no arg
	// int	i;

	// i = -1;
	// while (line[++i])
	// {
		if (line[0] == '-')
			return (0);
	// }
*/
int	find_arg(char *line)
{
	if (line[0] == '-')
		return (0);
	return (1);
}

/* 
! check if they may pass 
! cmd -op arg -arg
! check if arg_index is correct
*/
int	is_there_arg(t_mini_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->split[++i])
	{
		if (find_arg(cmd->split[i]))
		{
			cmd->tools.y_arg = 1;
			break ;
		}
	}
	if (cmd->tools.y_arg == 1)
		cmd->tools.arg_index = i;
	return (cmd->tools.arg_index);
}

// printf ("%d\n", is_there_arg(cmd));
void	check_arg(t_mini_cmd *cmd)
{
	if (is_there_arg(cmd))
		get_arg(cmd);
	else
		cmd->arguments = NULL;
}

// void	take_first_arg(t_mini_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	if (twstrlen(cmd->split) <= 1)
// 	{
// 		cmd->tools.arg_num = twstrlen(cmd->split) - 1;
// 		cmd->arguments = (char **)malloc(cmd->tools.arg_num * sizeof(char *));
// 		while (++i < cmd->tools.arg_num)
// 			cmd->arguments[i] = (char *)malloc(ft_strlen(cmd->split[i]));
// 	}
// 	else
// 		cmd->arguments = NULL;
// }
