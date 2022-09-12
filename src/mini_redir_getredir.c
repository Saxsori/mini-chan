/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_getredir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:43:40 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/11 07:33:05 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

char	*get_redir(char *line, int begin, int end)
{
	int		i;
	char	*redir;

	redir = (char *)malloc(sizeof(char) * (end - begin));
	i = 0;
	while (++begin < end)
		redir[i++] = line[begin];
	redir[i] = '\0';
	return (redir);
}

/*

			// printf ("r_valid %d\n", cmd->tools.p_redir.r_valid[redir_pos(cmd, i)]);
				// printf ("i - %d  e - %d\n", i - 1, e);
				// printf("----->redir %s\n", cmd->redir.redir[k]);
*/
void	fill_redir_array(t_mini_cmd *cmd, char *line)
{
	int	i;
	int	k;
	int	e;
	int	v;

	cmd->redir.redir = (char **)malloc(sizeof(char *) * (cmd->redir.redir_tools.num_redir + 1));
	cmd->redir.redir[cmd->redir.redir_tools.num_redir] = NULL;
	printf("v limit %d\n", cmd->redir.redir_tools.num_redir - 1);
	printf("k limit %d\n", cmd->tools.p_redir.num_redir);
	i = -1;
	k = 0;
	v = 0;
	while (++i < ft_strlen(line))
	{
		if (k < cmd->tools.p_redir.num_redir)
		{
			printf("k %d\n", k);
			if (cmd->tools.p_redir.r_index[k] == i)
			{
				// printf ("i----  %d pos %d\n", i, redir_pos(cmd, i));
				if (cmd->tools.p_redir.r_valid[redir_pos(cmd, i)] == -1)
				{
					e = is_more_redir(line, i);
					// printf("redir start %d, (%c) end %d, (%c) \n", i - 1, line[i], e, line[e]);
					printf("v %d\n", v);
					cmd->redir.redir[v] = get_redir(line, i - 1, e);
					printf ("redir %d %s\n", k, cmd->redir.redir[v]);
					v++;
				}
				k++;
			}
		}
		// printf ("k %d num r%d \n", v, cmd->redir.redir_tools.num_redir + 1);
		if (v == cmd->redir.redir_tools.num_redir + 1)
			break ;
	}
}
