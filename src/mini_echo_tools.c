/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:47:01 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/29 17:48:27 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	check_echo_opt(t_mini_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->option)
	{
		if (is_echo_opt(cmd->option, '1', 0))
		{
			cmd->tools.y_op = 1;
			if (is_echo_opt(cmd->option, 'i', cmd->tools.opt_num) != -1)
			{
				i = is_echo_opt(cmd->option, 'i', cmd->tools.opt_num) - 1;
				while (++i < cmd->tools.opt_num - 1)
					printf(BCYN"%s "BWHT, cmd->option[i]);
			}
		}
		else
			cmd->tools.y_op = 0;
	}
}

int	is_echo_opt(char **opt, char which, int len)
{
	int	i;

	i = 0;
	if (which == '1')
	{
		if (!ft_strncmp(opt[0], "-n", ft_strlen(opt[0])))
			return (1);
		return (0);
	}
	if (which == 'i')
	{
		while (++i < len)
		{
			if (ft_strncmp(opt[i], "-n", ft_strlen(opt[i])))
				return (i);
		}
		return (-1);
	}
	return (-1);
}
