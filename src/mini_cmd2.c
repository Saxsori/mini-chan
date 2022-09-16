/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:39:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/16 17:31:07 by aaljaber         ###   ########.fr       */
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
	int				i;
	int				status;

	status = 0;
	i = -1;
	if (cmd->option == NULL)
	{
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
			return (status);
		}
	}
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
		if (envar->prev == NULL)
			cmd->main->head_envar = \
						del_first_envar(cmd->main->head_envar);
		else if (envar->next == NULL)
			cmd->main->head_envar = \
						del_last_envar(cmd->main->head_envar);
		else
			del_mid_envar(envar);
	}
}
