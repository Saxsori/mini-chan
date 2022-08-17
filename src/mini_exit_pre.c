/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_pre.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:52:21 by balnahdi          #+#    #+#             */
/*   Updated: 2022/08/17 12:38:41 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../mini_chan.h"

char **get_exit_arg(t_mini_cmd *cmd)
{
	int		i;
	char 	**arg;
	int		num;
	int		j;

	num = cmd->tools.arg_num + cmd->tools.opt_num;
	printf("new_num %d\n", num);
	arg = (char **)malloc(sizeof(char *) * (num + 1));
	arg[num] = NULL;
	i = -1;
	while (++i < cmd->tools.opt_num)
		arg[i] = ft_strdup(cmd->option[i]);
	j = -1;
	while (++j < cmd->tools.arg_num)
		arg[i++] = ft_strdup(cmd->arguments[j]);
	squaredstr_free(cmd->arguments);
	squaredstr_free(cmd->option);
	cmd->tools.arg_num = num;
	cmd->tools.opt_num = 0;
	return (arg);
}

void	pre_exit_arg(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	printf("opt num %d\n", cmd->tools.opt_num);
	while(++i < cmd->tools.opt_num)
		printf("opt %s\n", cmd->option[i]);
	i = -1;
	printf("arg num %d\n", cmd->tools.arg_num);
	while(++i < cmd->tools.arg_num)
		printf("arg %s\n", cmd->arguments[i]);
	cmd->arguments = get_exit_arg(cmd);
	i = -1;
	printf("new arg num %d\n", cmd->tools.arg_num);
	while(++i < cmd->tools.arg_num)
		printf("new arg %s\n", cmd->arguments[i]);
}