/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:50:49 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/25 23:33:14 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	init_shell_chan(t_shell_chan *main)
{
	main->cmd_line = NULL;
	main->cmd_table = NULL;
	main->cmd_num = 0;
	main->exit_status = EXIT_SUCCESS;
	main->first_split = NULL;
	main->head_envar = NULL;
	main->exp_tools = NULL;
	main->exp_valid = NULL;
	main->env_index = NULL;
	main->envar = NULL;
	main->path = NULL;
	main->path_split = NULL;
	main->d_rootpath = 0;
	main->e_parse.new_size = 0;
	main->e_parse.null_num = 0;
}

void	re_init_shell_chan(t_shell_chan *main)
{
	free_shell_chan_mem(main);
	main->cmd_line = NULL;
	main->cmd_table = NULL;
	main->cmd_num = 0;
	main->first_split = NULL;
	main->exp_tools = NULL;
	main->exp_valid = NULL;
	main->env_index = NULL;
}


/****************************  PARSE_QUOTE  ***********************************/
/*
the beginning of the pars should be the beginning of the command line
-1 b/c it's ++i in loop
the end will be the last index which it should be the length of the 
command line
teh counter of the strings in th quotes should start from when first quotes
encountr so if the first char was quotes the counter should start 
from one instead of 0
*/
/*
? quotes checker
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
/****************************  PARSE_QUOTE  ***********************************/


/****************************  PARSE_REDIR  ***********************************/
/*
? redir tools
*/
void	init_predir(t_redir_parse *p_redir)
{
	p_redir->num_redir = 0;
	p_redir->begin = -1;
	p_redir->end = -1;
	p_redir->r_index = NULL;
	p_redir->r_valid = NULL;
}
/*
? redir tools
*/
void	init_predir_arrays(t_redir_parse *p_redir)
{
	int	i;

	i = -1;
	p_redir->r_index = (int *)malloc(sizeof(int) * p_redir->num_redir);
	p_redir->r_valid = (int *)malloc(sizeof(int) * p_redir->num_redir);
	while (++i < p_redir->num_redir)
	{
		p_redir->r_index[i] = -1;
		p_redir->r_valid[i] = -1;
	}
}
/*
? redir pre
*/
void	init_loop_p_redir(t_mini_cmd *cmd, int i)
{
	cmd->tools.p_redir.begin = -1;
	cmd->tools.p_redir.end = ft_strlen(cmd->main->first_split[i]);
}

/*
? split redir
*/
void	init_mini_redir(t_mini_redir *redir, t_shell_chan *main, int i)
{
	// int	k;

	redir->arguments = NULL;
	redir->command = NULL;
	redir->files = NULL;
	redir->redir_tools.main = main;
	redir->redir_tools.num_arg = 0;
	redir->redir_tools.num_file = 0;
	redir->redir_tools.parse_err = 0;
	redir->redir_tools.num_part = 0;
	redir->redir_tools.i = -1;
	redir->redir_tools.j = -1;
	redir->redir_tools.k = -1;
	redir->redir_tools.r_pos = NULL;
	// k = -1;
	// while (main->first_split[i][++k])
	// {
	// 	if (main->first_split[i][k] == '\a')
	// 		printf("yes\n");
	// }
	// printf("first split (%s)\n", main->first_split[i]);
	redir->redir_tools.split = ft_split(main->first_split[i], ' ');
	// k = -1;
	// while (redir->redir_tools.split[++k])
	// 	printf("split redir (%s)\n", redir->redir_tools.split[k]);
	replace_tabbing_spaces(redir->redir_tools.split);
}
/****************************  PARSE_REDIR  ***********************************/

/****************************  PARSE_EXPAND  ***********************************/
/*
? expand tools
*/
void	init_expand_tools(t_expand_tools *exp_tools, t_shell_chan *main, int index)
{
	exp_tools->main = main;
	exp_tools->index = index;
	exp_tools->env_num = envar_num(main, index);
	exp_tools->i_e = 0;
	exp_tools->pos = 0;
	exp_tools->i = -1;
	exp_tools->i_s = 0;
	exp_tools->env_info = NULL;
	if (exp_tools->env_num)
		exp_tools->env_info = (t_env_info *)malloc(sizeof(t_env_info) * exp_tools->env_num);
	exp_tools->new_exp_len = ft_strlen(exp_tools->main->first_split[index]);
	main->exp_tools = exp_tools;
}
/****************************  PARSE_EXPAND  ***********************************/



void	init_cmd_tools(t_mini_cmd *cmd)
{
	cmd->tools.arg_num = 0;
	cmd->tools.opt_num = 0;
	cmd->tools.arg_index = 0;
	cmd->tools.y_op = 0;
	cmd->tools.y_arg = 0;
	cmd->tools.i_arg = 0;
	cmd->tools.p_num = 0;
	cmd->tools.f_redir = 0;
	cmd->tools.y_redir = 0;
	cmd->tools.y_exe = 0;
	cmd->tools.new_arg = 0;
	cmd->tools.new_arg_size = 0;
	cmd->tools.r_err_syn = 0;
	cmd->tools.dir = NULL;
	cmd->tools.cwd_ret = NULL;
	cmd->tools.dir = NULL;
	cmd->tools.envar = NULL;
	cmd->tools.pwd = NULL;
	init_predir(&cmd->tools.p_redir);
}

void	init_mini_cmd(t_mini_cmd *cmd, t_shell_chan *main)
{
	cmd->main = main;
	cmd->name = NULL;
	cmd->split = NULL;
	cmd->option = NULL;
	cmd->arguments = NULL;
	cmd->cmd_path = NULL;
	init_cmd_tools(cmd);
	cmd->redir.arguments = NULL;
	cmd->redir.command = NULL;
	cmd->redir.files = NULL;
	cmd->redir.redir = NULL;
	cmd->redir.redir_tools.i = 0;
	cmd->redir.redir_tools.j = 0;
	cmd->redir.redir_tools.k = 0;
	cmd->redir.redir_tools.main = NULL;
	cmd->redir.redir_tools.num_arg = 0;
	cmd->redir.redir_tools.num_file = 0;
	cmd->redir.redir_tools.num_part = 0;
	cmd->redir.redir_tools.num_redir = 0;
	cmd->redir.redir_tools.parse_err = 0;
	cmd->redir.redir_tools.r_pos = NULL;
	cmd->redir.redir_tools.split = NULL;
}













































// void	init_mem_cmd(t_mini_cmd *cmd)
// {
// 	printf("hello poop\n");
// 	cmd->name = NULL;
// 	cmd->split = NULL;
// 	cmd->option = NULL;
// 	cmd->arguments = NULL;
// 	cmd->tools.cwd_ret = NULL;
// 	cmd->tools.dir = NULL;
// 	cmd->tools.envar = NULL;
// 	cmd->tools.pwd = NULL;
// 	// cmd->redir.arguments = NULL;
// 	// cmd->redir.command = NULL;
// 	// cmd->redir.files = NULL;
// 	// cmd->redir.redir = NULL;
// }






















// void	free_mini_redir(t_mini_redir *redir)
// {
// 	squaredstr_free(redir->redir_tools.split);
// 	free(redir->redir_tools.r_pos);
// 	free(redir->command);
// 	squaredstr_free(redir->redir);
// 	squaredstr_free(redir->arguments);
// 	squaredstr_free(redir->files);
// }

// void	free_mini_cmd(t_mini_cmd *cmd)
// {
// 	if (cmd->split != NULL)
// 		squaredstr_free(cmd->split);
// 	if (cmd->option != NULL)
// 		squaredstr_free(cmd->option);
// 	if (cmd->arguments != NULL)
// 		squaredstr_free(cmd->arguments);
// 	if (cmd->name != NULL)
// 		free (cmd->name);
// 	if (cmd->tools.cwd_ret != NULL)
// 		free (cmd->tools.cwd_ret);
// 	if (cmd->tools.pwd != NULL)
// 		free (cmd->tools.pwd);
// 	if (cmd->tools.f_redir)
// 		free_redir_parse(cmd);
// 	if (cmd->tools.y_redir)
// 		free_mini_redir(&cmd->redir);
// 	init_mem_cmd(cmd);
// 	// // free DIR
// }








// void	re_init_env_expand(t_env_expand *exp_tools)
// {
// 	exp_tools->start = 0;
// 	exp_tools->end = 0;
// 	exp_tools->name_len = 0;
// }






void	init_mini_pipe(t_mini_pipe *p_tool)
{
	p_tool->fds = NULL;
	p_tool->child = -1;
	p_tool->i = 0;
	p_tool->j = 0;
	p_tool->p_num = 0;
	p_tool->status = 0;

}