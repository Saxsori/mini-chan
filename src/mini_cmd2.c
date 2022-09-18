/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:39:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/18 10:53:12 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

		// printf(BRED"export: no option: %s\n", cmd->option[0]);
int	mini_export(t_mini_cmd *cmd)
{
	if (cmd->option == NULL)
	{
		if (cmd->arguments)
			return (do_export(cmd));
		else
		{
			print_envar_list(cmd->main->head_envar, 'x');
			return (0);
		}
	}
	else
		errmsg("export", "no option");
	return (1);
}

		// printf(BRED"unset: no option: %s\n", cmd->option[0]);
int	mini_unset(t_mini_cmd *cmd)
{
	if (cmd->option == NULL)
		return (start_unset(cmd));
	else
		errmsg("unset", "no option");
	return (2);
}

	// if (!cmd->arguments)
int	mini_env(t_mini_cmd *cmd)
{
	print_envar_list(cmd->main->head_envar, 'n');
	return (0);
}

int	mini_chan(void)
{
	printf(BCYN"%s", MINI_CHAN);
	new_prompt(1);
	return (0);
}
