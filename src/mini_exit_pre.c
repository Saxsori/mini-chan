/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_pre.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:52:21 by balnahdi          #+#    #+#             */
/*   Updated: 2023/01/21 00:19:16 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../incl/mini_chan.h"

void	free_previous_parts(t_mini_cmd *cmd)
{
	if (cmd->arguments)
	{
		squaredstr_free(cmd->arguments);
		cmd->arguments = NULL;
	}
	if (cmd->option)
	{
		squaredstr_free(cmd->option);
		cmd->option = NULL;
	}
}

char	**get_exit_arg(t_mini_cmd *cmd)
{
	int		i;
	char	**arg;
	int		num;
	int		j;

	num = cmd->tools.arg_num + cmd->tools.opt_num;
	arg = (char **)malloc(sizeof(char *) * (num + 1));
	arg[num] = NULL;
	i = -1;
	while (++i < cmd->tools.opt_num)
		arg[i] = ft_strdup(cmd->option[i]);
	j = -1;
	while (++j < cmd->tools.arg_num)
		arg[i++] = ft_strdup(cmd->arguments[j]);
	free_previous_parts(cmd);
	cmd->tools.arg_num = num;
	cmd->tools.opt_num = 0;
	return (arg);
}

/*

	int	i;

	i = -1;
	printf("222seg\n");
	printf("opt num %d\n", cmd->tools.opt_num);
	while (++i < cmd->tools.opt_num)
		printf("opt %s\n", cmd->option[i]);
	i = -1;
	printf("arg num %d\n", cmd->tools.arg_num);
	while (++i < cmd->tools.arg_num)
		printf("arg %s\n", cmd->arguments[i]);
	i = -1;
	printf("new arg num %d\n", cmd->tools.arg_num);
	while (++i < cmd->tools.arg_num)
		printf("new arg %s\n", cmd->arguments[i]);
*/
void	pre_exit_arg(t_mini_cmd *cmd)
{
	cmd->arguments = get_exit_arg(cmd);
}
