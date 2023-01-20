/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_getred.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:38:03 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

char	*get_redir(char *line, int begin, int end)
{
	int		i;
	char	*redir;

	redir = (char *)malloc(sizeof(char) * (end - begin));
	i = 0;
	printf("1 begin %d\n", begin);
	while (++begin < end)
	{
		redir[i++] = line[begin];
		printf("begin %d\n", begin);
	}
	redir[i] = '\0';
	return (redir);
}

void	fill_redir_array(t_mini_cmd *cmd, char *line)
{
	int	i;
	int	k;
	int	e;

	cmd->redir.redir = (char **)malloc(sizeof(char *) * cmd->redir.redir_tools.num_redir + 1);
	cmd->redir.redir[cmd->redir.redir_tools.num_redir] = NULL;
	i = -1;
	k = 0;
	while (++i < ft_strlen(line))
	{
		if (cmd->tools.p_redir.r_index[k] == i)
		{
			printf ("r_valid %d\n", cmd->tools.p_redir.r_valid[redir_pos(cmd, i)]);
			if (cmd->tools.p_redir.r_valid[redir_pos(cmd, i)] == -1)
			{
				e = is_more_redir(line, i);
				printf ("i - %d  e - %d\n", i - 1, e);
				cmd->redir.redir[k] = get_redir(line, i - 1, e);
				printf("----->redir %s\n", cmd->redir.redir[k]);
			}
			k++;
		}
		if (k == cmd->redir.redir_tools.num_redir + 1)
			break ;
	}
}
