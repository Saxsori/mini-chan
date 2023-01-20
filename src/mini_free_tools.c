/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_free_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:17:21 by balnahdi          #+#    #+#             */
/*   Updated: 2023/01/21 00:18:46 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/mini_chan.h"

void	squaredstr_free(char **array)
{
	int		i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
	}
	free(array);
}

void	squaredint_free(int **array, int len)
{
	int		i;

	i = -1;
	while (++i < len)
		free(array[i]);
	free(array);
}

void	free_ptr(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

	// rl_clear_history();
void	ft_exit(t_shell_chan *main, int status)
{
	if (main->path_split)
		squaredstr_free(main->path_split);
	if (main->path)
		free_ptr((void **)&main->path);
	free_shell_chan_mem(main);
	free_mini_chan(main);
	exit(status);
}

void	free_mini_chan(t_shell_chan *main)
{
	free_mini_envar(main);
}
