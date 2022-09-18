/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balnahdi <balnahdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:50:49 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/18 14:48:24 by balnahdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/****************************  MAIN_STRUCT  ***********************************/
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
	main->d_rootpath = 0;
	main->path = NULL;
	main->path_split = NULL;
	main->e_parse.new_size = 0;
	main->e_parse.null_num = 0;
	main->f_pwd = 0;
	main->no_path = 0;
	init_mini_pipe(&main->pipe_tools);
	init_null_parse(&main->n_parse);
}

void	re_init_shell_chan(t_shell_chan *main)
{
	free_shell_chan_mem(main);
	if (main->path_split)
		squaredstr_free(main->path_split);
	if (main->path)
		free_ptr((void **)&main->path);
	main->path = NULL;
	main->path_split = NULL;
	main->cmd_line = NULL;
	main->cmd_table = NULL;
	main->cmd_num = 0;
	main->first_split = NULL;
	main->exp_tools = NULL;
	main->exp_valid = NULL;
	main->env_index = NULL;
	main->d_rootpath = 0;
	main->pipe_tools.fds = NULL;
	main->pipe_tools.i = 0;
	main->pipe_tools.j = 0;
	main->pipe_tools.p_num = 0;
	main->pipe_tools.child = NULL;
	main->pipe_tools.status = 0;
	main->e_parse.new_size = 0;
	main->e_parse.null_num = 0;
	main->exit_status = EXIT_SUCCESS;
}
/****************************  MAIN_STRUCT  ***********************************/

/****************************  PARSE_EXPAND  ******************************/
/*
? expand tools
*/
void	init_expand_tools(t_expand_tools *exp_tools, \
t_shell_chan *main, int index)
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
		exp_tools->env_info = (t_env_info *)malloc(sizeof(t_env_info) * \
		exp_tools->env_num);
	exp_tools->new_exp_len = ft_strlen(exp_tools->main->first_split[index]);
	main->exp_tools = exp_tools;
}
/****************************  PARSE_EXPAND  *****************************/

/****************************  PIPE  ***********************************/
void	init_mini_pipe(t_mini_pipe *p_tool)
{
	p_tool->fds = NULL;
	p_tool->child = NULL;
	p_tool->i = 0;
	p_tool->j = 0;
	p_tool->p_num = 0;
	p_tool->status = 0;
}
/****************************  PIPE  ***********************************/

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
