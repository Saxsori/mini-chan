/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_arg_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:24:02 by aaljaber          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

int	get_arg_pos(t_mini_redir *redir)
{
	int	i;

	i = 0;
	if (redir->arguments[1][0] == '-')
	{
		while (++i < redir->redir_tools.num_arg + 1)
		{
			if (!is_echo_opt(redir->arguments[i]))
				return (i - 1);
		}
	}
	return (0);
}

/*
debug

*/
void	get_echo_arg_redir(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	i = get_arg_pos(&cmd->redir);
	k = -1;
	// printf("i %d\n", i);
	// printf("num_arg - i = %d\n", cmd->redir.redir_tools.num_arg - i);
	squaredstr_free(cmd->arguments);
	// printf("hi\n");
	cmd->tools.arg_num = cmd->redir.redir_tools.num_arg - i;
	cmd->arguments = (char **)malloc((cmd->tools.arg_num + 1) * sizeof(char *));
	cmd->arguments[cmd->redir.redir_tools.num_arg - i] = NULL;
	// i = -1;
	while (++i < cmd->redir.redir_tools.num_arg + 1)
	{
		cmd->arguments[++k] = ft_strdup(cmd->redir.arguments[i]);
		// printf("re arg ---> %s\n", cmd->redir.arguments[i]);
		// printf("arg ---> %s\n", cmd->arguments[k]);
	}
	// printf("hi\n");
}
