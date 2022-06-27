/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:05:04 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/27 20:53:04 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	mini_execute(t_mini_cmd *cmd)
{
	int				i;
	t_mini_envar	*envar;
	char			*path;
	char			**path_split;

	envar = search_envar(cmd->main->head_envar, "PATH");
	path = ft_strdup(envar->env_cont);
	path_split = ft_split(path, ':');
	i = 0;
	while (path_split[i])
	{
		if(access(ft_strjoin((ft_strjoin(path_split[i], "/")), cmd->exe_tools.cmd_name),F_OK) == 0)
			cmd->exe_tools.cmd_name = ft_strjoin((ft_strjoin(path_split[i],"/")), cmd->exe_tools.cmd_name);
		i++;
	}
	
	i = -1;
	printf("nun %d\n", cmd->exe_tools.arg_num);
	printf("con %s\n", cmd->exe_tools.cmd_name);
	while (++i < cmd->exe_tools.arg_num)
		printf("arg %s\n", cmd->exe_tools.arguments[i]);
	
	if(execve(cmd->exe_tools.cmd_name, cmd->exe_tools.arguments, NULL) == -1)
		perror("Error\n");
}
