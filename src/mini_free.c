/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:24:52 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/25 16:31:04 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	squaredstr_free(char **array)
{
	int		i;

	i = -1;
	while (array[++i])
		free(array[i]);
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
	free_ptr((void **)&cmd->tools.p_redir.r_index);
	free_ptr((void **)&cmd->tools.p_redir.r_valid);
}

void	free_redir(t_mini_cmd *cmd)
{
	if (cmd->redir.command)
		free_ptr((void **)&cmd->redir.command);
	if (cmd->redir.redir_tools.r_pos)
		free_ptr((void **)&cmd->redir.redir_tools.r_pos);
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
}

void	free_mini_cmd(t_mini_cmd *cmd)
{
	free_predir(cmd);
	free_redir(cmd);
}

void	free_shell_chan_mem(t_shell_chan *main)
{
	int	i;

	i = -1;
	if (main->cmd_line)
		free_ptr((void **)&main->cmd_line);
	if (main->first_split)
		squaredstr_free(main->first_split);
	// if (main->exp_tools)
	// 	free_ptr((void **)&main->exp_tools);
	if (main->exp_valid)
		squaredint_free(main->exp_valid, main->cmd_num);
	if (main->env_index)
		squaredint_free(main->env_index, main->cmd_num);
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
	if (main->path)
		free_ptr((void **)main->path);
	if (main->path_split)
		squaredstr_free(main->path_split);
}

void	ft_exit(t_shell_chan *main, int	status)
{
	free_shell_chan_mem(main);
	free_mini_chan(main);
	exit(status);
}
