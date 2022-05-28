/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:39:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/28 19:41:15 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	mini_export(t_mini_cmd *cmd)
{
	cmd->main->head_envar = add_node_at_end(cmd->main->head_envar, cmd->arguments[0]);
	return (1);
}

int	mini_unset(t_mini_cmd *cmd)
{
	(void) cmd;
	printf("unset was here\n");
	return (1);
}

int	mini_env(t_mini_cmd *cmd)
{
	if (!cmd->arguments)
		print_envar_list(cmd->main->head_envar);
	else
	{
		print_envar_list(cmd->main->head_envar);
		printf(BCYN"%s\n"BWHT, cmd->arguments[0]);
	}
	return (1);
}
