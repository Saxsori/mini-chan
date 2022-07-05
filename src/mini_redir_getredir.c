/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_redir_getredir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:43:40 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/04 04:22:49 by aaljaber         ###   ########.fr       */
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

	cmd->redir.redir = (char **)malloc(sizeof(char *) * cmd->redir.redir_tools.num_redir + 1);
	cmd->redir.redir[cmd->redir.redir_tools.num_redir] = NULL;
	i = -1;
	k = 0;
	while (++i < ft_strlen(line))
	{
		if (cmd->tools.p_redir.r_index[k] == i)
		{
			if (cmd->tools.p_redir.r_valid[redir_pos(cmd, i)] == -1)
			{
				e = is_more_redir(line, i);
				cmd->redir.redir[k] = get_redir(line, i - 1, e);
			}
			k++;
		}
		if (k == cmd->redir.redir_tools.num_redir + 1)
			break ;
	}
}
