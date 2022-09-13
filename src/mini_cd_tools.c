/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 04:27:25 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/13 12:10:40 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	is_doubslash(char *line)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '/')
			k++;
	}
	return (k);
}

void	check_root(t_mini_cmd *cmd)
{
	if (is_doubslash(cmd->arguments[0]) == 2)
		cmd->main->d_rootpath = 1;
	else if (is_doubslash(cmd->arguments[0]) != 2 \
			&& is_doubslash(cmd->arguments[0]) != 0)
		cmd->main->d_rootpath = 0;
}
