/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:50:49 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/12 06:56:07 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	init_shell_chan(t_shell_chan *main)
{
	main->cmd_line = NULL;
	main->cmd_num = 0;
	main->exit_status = EXIT_SUCCESS;
	main->d_rootpath = 0;
}

void	re_init_shell_chan(t_shell_chan *main)
{
	// if (main->exp_valid != NULL)
	// 	squaredint_free(main->exp_valid, main->cmd_num);
	// if (main->env_index != NULL)
	// 	squaredint_free(main->env_index, main->cmd_num);
	main->cmd_num = 0;
	main->exp_valid = NULL;
	main->env_index = NULL;
}

void	init_mini_cmd(t_mini_cmd *cmd, t_shell_chan *main)
{
	cmd->arguments = NULL;
	cmd->option = NULL;
	cmd->main = main;
	cmd->tools.arg_num = 0;
	cmd->tools.opt_num = 0;
	cmd->tools.arg_index = 0;
	cmd->tools.y_op = 0;
	cmd->tools.y_arg = 0;
	cmd->tools.p_num = 0;
}

/*
the beginning of the pars should be the beginning of the command line
-1 b/c it's ++i in loop
the end will be the last index which it should be the length of the 
command line
teh counter of the strings in th quotes should start from when first quotes
encountr so if the first char was quotes the counter should start 
from one instead of 0
*/
void	init_mini_quotes(t_shell_chan *main, char *line)
{
	main->q_pars.begin = -1;
	main->q_pars.end = ft_strlen(line);
	if (line[0] != 34 && line[0] != 39)
		main->q_pars.q_string = 1;
	else
		main->q_pars.q_string = 0;
	main->q_pars.first = 0;
	main->q_pars.second = 0;
	main->q_pars.exp_index = 0;
}

// 	exp_tools->env_ord = 0;
// 	exp_tools->start = 0;
// 	exp_tools->end = 0;
// 	exp_tools->name_len = 0;
// 	exp_tools->env_ptr = NULL;
// 	exp_tools->new_len_exp = ft_strlen(main->first_split[index]);
// 	exp_tools->l = -1;
void	init_expand_tools(t_expand_tools *exp_tools, t_shell_chan *main, int index)
{
	exp_tools->main = main;
	exp_tools->index = index;
	exp_tools->env_num = envar_num(main, index);
	exp_tools->e = 0;
	exp_tools->i = -1;
	exp_tools->s = 0;
	if (exp_tools->env_num)
		exp_tools->env_info = (t_env_info*)malloc(sizeof(t_env_info) * exp_tools->env_num);
	exp_tools->new_exp_len = 0;
	main->exp_tools = exp_tools;
}

// void	re_init_env_expand(t_env_expand *exp_tools)
// {
// 	exp_tools->start = 0;
// 	exp_tools->end = 0;
// 	exp_tools->name_len = 0;
// }
