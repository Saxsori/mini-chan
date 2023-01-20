/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:20:20 by balnahdi          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

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
