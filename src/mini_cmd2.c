/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:39:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/29 00:07:09 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	mini_export(t_mini_cmd *cmd)
{
	if (cmd->arguments)
	{
		cmd->main->head_envar = \
			add_node_at_end(cmd->main->head_envar, cmd->arguments[0]);
		return (1);
	}
	return (0);
}

int	mini_unset(t_mini_cmd *cmd)
{
	t_mini_envar	*envar;
	int				i;

	i = -1;
	if (cmd->arguments)
	{
		while (cmd->arguments[++i])
		{
			envar = sreach_envar(cmd->main->head_envar, cmd->arguments[i]);
			if (envar)
			{
				if (envar->prev == NULL)
					cmd->main->head_envar = del_first_envar(cmd->main->head_envar);
				else if (envar->next == NULL)
					cmd->main->head_envar = del_last_envar(cmd->main->head_envar);
				else
					del_mid_envar(envar);
			}
			return(1);
				// printf(BGRN"%s=%s\n"BWHT, envar->env_name, envar->env_cont);
			// if ()
			// if (envar && envar->prev && !envar->next)
			// else if (envar)
		}
	}
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
