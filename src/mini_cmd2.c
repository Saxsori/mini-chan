/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:39:29 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/13 12:15:19 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

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
		printf(BRED"export: no option: %s\n", cmd->option[0]);
	return (1);
}

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
				if (isvalid_name(cmd->arguments[i]))
					do_unset(cmd, i);
				else
				{
					printf(BRED"mini-chan🌸: unset: `%s': not a valid identifier\n"BCYN, cmd->arguments[i]);
					status = 1;
				}
			}
			return (status);
		}
	}
	else
		printf(BRED"unset: no option: %s\n", cmd->option[0]);
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
	printf(BCYN "\nThis shell has been raised (created) with\nunconditional love (anger), in a hope to be \na successful happy shell in the future ^◡^ \n");
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
				cmd->main->f_pwd = 1;
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
