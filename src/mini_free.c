/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:29:06 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/16 07:29:21 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	squaredstr_free(char **array)
{
	int		i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
	}
	free(array);
}

void	squaredint_free(int **array, int len)
{
	int		i;

	i = -1;
	while (++i < len)
		free(array[i]);
	free(array);
}

void	free_ptr(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_predir(t_mini_cmd *cmd)
{
	if (cmd->tools.p_redir.r_index)
		free_ptr((void **)&cmd->tools.p_redir.r_index);
	if (cmd->tools.p_redir.r_valid)
		free_ptr((void **)&cmd->tools.p_redir.r_valid);
}

void	free_redir(t_mini_cmd *cmd)
{
	if (cmd->redir.command)
		free_ptr((void **)&cmd->redir.command);
	if (cmd->redir.arguments)
		squaredstr_free(cmd->redir.arguments);
	if (cmd->redir.files)
		squaredstr_free(cmd->redir.files);
	if (cmd->redir.redir)
		squaredstr_free(cmd->redir.redir);
	if (cmd->redir.redir_tools.r_pos)
		free_ptr((void **)&cmd->redir.redir_tools.r_pos);
	if (cmd->redir.redir_tools.split)
		squaredstr_free(cmd->redir.redir_tools.split);
	if (cmd->redir.redir_tools.fd)
		squaredint_free(cmd->redir.redir_tools.fd, 2);
}

void	free_cmd_tools(t_mini_cmd *cmd)
{
	if (cmd->tools.pwd)
		free_ptr((void **)&cmd->tools.pwd);
	if (cmd->tools.dir)
		free_ptr((void **)&cmd->tools.dir);
}

void	free_exe_tools(t_mini_cmd *cmd)
{
	if (cmd->exe_tools.cmd_name)
		free_ptr((void **)&cmd->exe_tools.cmd_name);
	if (cmd->exe_tools.err_command)
		free_ptr((void **)&cmd->exe_tools.err_command);
	if (cmd->exe_tools.arguments)
		squaredstr_free(cmd->exe_tools.arguments);
}

void	free_mini_cmd(t_mini_cmd *cmd)
{
	if (cmd->name)
		free_ptr((void **)&cmd->name);
	if (cmd->split)
		squaredstr_free(cmd->split);
	if (cmd->option)
		squaredstr_free(cmd->option);
	if (cmd->arguments)
		squaredstr_free(cmd->arguments);
	if (cmd->cmd_path)
		free_ptr((void **)&cmd->cmd_path);
	free_exe_tools (cmd);
	free_cmd_tools(cmd);
	free_predir(cmd);
	free_redir(cmd);
}

void	free_shell_chan_mem(t_shell_chan *main)
{
	int	i;

	i = -1;
	if (main->pipe_tools.fds)
		squaredint_free(main->pipe_tools.fds, main->cmd_num - 1);
	if (main->pipe_tools.child)
		free_ptr((void **)&main->pipe_tools.child);
	if (main->path)
		free_ptr((void **)&main->path);
	if (main->cmd_line)
		free_ptr((void **)&main->cmd_line);
	if (main->first_split)
		squaredstr_free(main->first_split);
	if (main->exp_valid)
		squaredint_free(main->exp_valid, main->cmd_num);
	if (main->env_index)
		squaredint_free(main->env_index, main->cmd_num);
	if (main->n_parse.new_line)
		free_ptr((void **)&main->n_parse.new_line);
	if (main->cmd_table)
	{
		while (++i < main->cmd_num)
			free_mini_cmd(&main->cmd_table[i]);
		free_ptr((void **)&main->cmd_table);
	}
}

void	free_mini_envar(t_shell_chan *main)
{
	t_mini_envar	*traversal;
	t_mini_envar	*node;

	node = main->head_envar;
	while (node)
	{
		traversal = node->next;
		if (node->env_name)
			free(node->env_name);
		if (node->envar)
			free(node->envar);
		if (node->env_cont)
			free(node->env_cont);
		free(node);
		node = traversal;
	}
}

void	free_mini_chan(t_shell_chan *main)
{
	free_mini_envar(main);
}

void	ft_exit(t_shell_chan *main, int	status)
{
	// rl_clear_history();
	if (main->path_split)
		squaredstr_free(main->path_split);
	if (main->path)
		free_ptr((void **)&main->path);
	free_shell_chan_mem(main);
	free_mini_chan(main);
	exit(status);
}
