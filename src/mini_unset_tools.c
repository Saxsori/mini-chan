/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:48:04 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

int	start_unset(t_mini_cmd *cmd)
{
	int				i;
	int				status;

	status = 0;
	i = -1;
	if (cmd->arguments)
	{
		while (++i < cmd->tools.arg_num)
		{
			if (isvalid_name(cmd->arguments[i]) && !is_equal(cmd->arguments[i]))
				do_unset(cmd, i);
			else
			{
				errmsg(cmd->arguments[i], NVI);
				status = 1;
			}
		}
	}
	return (status);
}

void	unset_action(t_mini_cmd *cmd, t_mini_envar *envar)
{
	if (envar->prev == NULL)
		cmd->main->head_envar = \
					del_first_envar(cmd->main->head_envar);
	else if (envar->next == NULL)
		cmd->main->head_envar = \
					del_last_envar(cmd->main->head_envar);
	else
		del_mid_envar(envar);
}

/*
! cd case 
		// if (!ft_strncmp(cmd->arguments[i], "PWD", ft_strlen(cmd->arguments[i])))
		// {
		// 	cmd->tools.envar = search_envar(cmd->main->head_envar, "OLDPWD");
		// 	cmd->tools.envar->declared = 1;
		// }
*/
void	do_unset(t_mini_cmd *cmd, int i)
{
	t_mini_envar	*envar;

	envar = search_envar(cmd->main->head_envar, cmd->arguments[i]);
	if (envar)
	{
		if (!ft_strncmp(cmd->arguments[i], "PWD", ft_strlen(cmd->arguments[i])))
		{
			cmd->tools.envar = search_envar(cmd->main->head_envar, "PWD");
			if (cmd->tools.envar)
			{
				cmd->main->f_pwd = 1;
				cmd->tools.envar->declared = 0;
				return ;
			}
		}
		if (!ft_strncmp(cmd->arguments[i], "PATH", \
		ft_strlen(cmd->arguments[i])))
		{
			cmd->tools.envar = search_envar(cmd->main->head_envar, "PATH");
			if (cmd->tools.envar)
				cmd->main->no_path = 1;
		}
		unset_action(cmd, envar);
	}
}
