/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:24:52 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

void	squaredstr_free(char **array)
{
	int		i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = NULL;
}

void	squaredint_free(int **array, int len)
{
	int		i;

	i = -1;
	while (++i < len)
		free(array[i]);
	free(array);
	array = NULL;
}

void	free_ptr(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_shell_chan_mem(t_shell_chan *main)
{
	if (main->cmd_line)
		free_ptr((void **)&main->cmd_line);
	if (main->cmd_table)
		free_ptr((void **)&main->cmd_table);
	if (main->first_split)
		squaredstr_free(main->first_split);
	if (main->exp_tools)
		free_ptr((void **)&main->exp_tools);
	if (main->exp_valid)
		squaredint_free(main->exp_valid, main->cmd_num);
	if (main->env_index)
		squaredint_free(main->env_index, main->cmd_num);
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
		if (node->env_cont)
			free(node->env_cont);
		if (node->envar)
			free(node->envar);
		free(node);
		node = traversal;
	}
	if (main->head_envar->env_cont)
		free(main->head_envar->env_cont);
	if (main->head_envar->env_name)
		free(main->head_envar->env_name);
	if (main->head_envar->envar)
		free(main->head_envar->envar);
	free(main->head_envar);
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
