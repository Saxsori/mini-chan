/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_getredir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:43:40 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 08:11:00 by aaljaber         ###   ########.fr       */
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

void	init_fill_redir_array(t_mini_cmd *cmd, int *i, int *k, int *v)
{
	*i = -1;
	*k = 0;
	*v = 0;
	cmd->redir.redir = (char **)malloc(sizeof(char *) * \
	(cmd->redir.redir_tools.num_redir + 1));
	cmd->redir.redir[cmd->redir.redir_tools.num_redir] = NULL;
}

/*
// printf ("r_valid %d\n", cmd->tools.p_redir.r_valid[redir_pos(cmd, i)]);
// printf ("i - %d  e - %d\n", i - 1, e);
// printf("----->redir %s\n", cmd->redir.redir[k]);
// printf("v limit %d\n", cmd->redir.redir_tools.num_redir - 1);
// printf("k limit %d\n", cmd->tools.p_redir.num_redir);
// printf ("i----  %d pos %d\n", i, redir_pos(cmd, i));
// printf("k %d\n", k);
// printf("v %d\n", v);
// printf("redir start %d, (%c) end %d, (%c) \n", i - 1, line[i], e, line[e]);
// printf ("redir %d %s\n", k, cmd->redir.redir[v]);
// printf ("k %d num r%d \n", v, cmd->redir.redir_tools.num_redir + 1);
*/
void	fill_redir_array(t_mini_cmd *cmd, char *line)
{
	int	i;
	int	k;
	int	e;
	int	v;

	init_fill_redir_array(cmd, &i, &k, &v);
	while (++i < ft_strlen(line))
	{
		if (k < cmd->tools.p_redir.num_redir)
		{
			if (cmd->tools.p_redir.r_index[k] == i)
			{
				if (cmd->tools.p_redir.r_valid[redir_pos(cmd, i)] == -1)
				{
					e = is_more_redir(line, i);
					cmd->redir.redir[v] = get_redir(line, i - 1, e);
					v++;
				}
				k++;
			}
		}
		if (v == cmd->redir.redir_tools.num_redir + 1)
			break ;
	}
}
