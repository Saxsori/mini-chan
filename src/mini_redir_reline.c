/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_reline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 03:03:19 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/04 04:13:58 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	isvla_redir(t_mini_cmd *cmd, int index)
{
	int	i;

	i = -1;
	while (++i < cmd->tools.p_redir.num_redir)
	{
		if (cmd->tools.p_redir.r_index[i] == index)
		{
			if (cmd->tools.p_redir.r_valid[i] == -1)
				return (1);
		}
	}
	return (0);
}

char	*replace_redir(char	*line, t_mini_cmd *cmd)
{
	char	*new;
	int		len;
	int		i;
	int		k;
	int		end;

	len = ft_strlen(line) + (cmd->redir.redir_tools.num_redir * 2);
	new = (char *)malloc(sizeof(char) * (len + 1));
	i = -1;
	k = 0;
	while (++i < ft_strlen(line))
	{
		if (isvla_redir(cmd, i))
		{
			new[k++] = ' ';
			end = is_more_redir(line, i);
			while (i++ < end)
				new[k++] = '\a';
			i -= 2;
			new[k++] = ' ';
		}
		else
			new[k++] = line[i];
	}
	new[k] = '\0';
	free(line);
	return (new);
}