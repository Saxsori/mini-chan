/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:54:58 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/16 13:56:36 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	get_builtin_cmd(t_mini_cmd *cmd)
{
	free(cmd->name);
	if (cmd->redir.command)
		cmd->name = ft_strdup(cmd->redir.command);
	else
		cmd->name = NULL;
}

void	get_builtin_arg(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	get_builtin_cmd(cmd);
	if (cmd->arguments)
	{
		squaredstr_free(cmd->arguments);
		cmd->arguments = NULL;
		cmd->tools.arg_num = 0;
	}
	if (cmd->redir.redir_tools.num_arg)
	{
		cmd->tools.arg_num = cmd->redir.redir_tools.num_arg;
		cmd->arguments = (char **)malloc(sizeof(char *) * \
		(cmd->redir.redir_tools.num_arg + 1));
		cmd->arguments[cmd->redir.redir_tools.num_arg] = NULL;
		while (++i < (cmd->redir.redir_tools.num_arg + 1))
		{
			cmd->arguments[k] = ft_strdup(cmd->redir.arguments[i]);
			k++;
		}
	}
}

/*
! b4 u put them in their places check for the qoutes
! check for the environmental variables ^.^
! check for opt is postponded till know if u may get '-' when it's arg
// check_opt(main);
// void	check_opt(t_shell_chan *)
// if (ft_strchr(main->cmd_table[i].split[k], '-'))
	// 	}
	// 	printf("opt num %d\n", main->cmd_table->tools.opt_num);
	// 	printf("arg num %d\n", main->cmd_table->tools.arg_num);
	// 	// printf("1:%d\n", main->cmd_num);
	// 	// printf("2:%d\n", main->cmd_table[i].main->cmd_num);
// 	// i = -1;
// 	// while (++i < main->cmd_num)
// 	// {
// 	// 	k = -1;
// 	// 	while (++k < main->cmd_table->tools.opt_num)
// 	// 	{
// 	// 		printf("opt %s\n", main->cmd_table[i].option[k]);
// 	// 	}
// 	// 	k = -1;
// 	// 	while (++k < main->cmd_table->tools.arg_num)
// 	// 	{
// 	// 		printf("arg %s\n", main->cmd_table[i].arguments[k]);
// 	// 	}
// 	// }
*/
void	check_cmd_parts(t_shell_chan *main)
{
	int	i;

	i = -1;
	while (++i < main->cmd_num)
	{
		check_opt(&main->cmd_table[i]);
		check_arg(&main->cmd_table[i]);
		if (main->cmd_table[i].tools.y_redir)
			get_builtin_arg(&main->cmd_table[i]);
	}
}

void	check_isbuiltin(t_shell_chan *main)
{
	int		i;
	char	**split;

	i = -1;
	while (++i < main->cmd_num)
	{
		split = ft_split(main->first_split[i], ' ');
		if (split)
		{
			if (is_command(split[0]))
				main->cmd_table[i].tools.y_exe = 0;
			else
				main->cmd_table[i].tools.y_exe = 1;
			squaredstr_free(split);
		}
	}
}
