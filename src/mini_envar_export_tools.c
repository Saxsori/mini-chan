/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_envar_export_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:57:03 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/22 17:01:41 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
to replace the valude of the envar
*/
void	replace_envar(t_mini_cmd *cmd, int i)
{
	char			**arg;
	t_mini_envar	*envar;

	arg = ft_split(cmd->arguments[i], '=');
	envar = search_envar(cmd->main->head_envar, arg[0]);
	if (envar)
	{
		if (envar->prev == NULL)
			cmd->main->head_envar = \
							del_first_envar(cmd->main->head_envar);
		else if (envar->next == NULL)
			cmd->main->head_envar = \
							del_last_envar(cmd->main->head_envar);
		else
			del_mid_envar(envar);
	}
	add_node_at_end(cmd->main->head_envar, cmd->arguments[i], 'n');
	squaredstr_free(arg);
}

/*
to check if the name is valid
*/
int	isvalid_name(char *line)
{
	int	i;

	i = -1;
	if ((!ft_isalpha(line[0]) && line[0] != '_' && line [0] == '=') || ft_isdigit(line[0]))
		return (0);
	while (++i < ft_strlen(line) && line[i])
	{
		if (line[i] == '=')
			return (1);
		if (!ft_isalpha(line[i]) && !ft_isdigit(line[i]) && line[i] != '_')
			return (0);
	}
	return (1);
}

/*
to check if there is =
*/
int	is_equal(char *line)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(line))
	{
		if (line[i] == '=')
			return (1);
	}
	return (0);
}

/*
to check if the envar is there already
*/
int	check_is_name_there(t_shell_chan *main, char *line)
{
	char	**arg;

	arg = ft_split(line, '=');
	if (search_envar(main->head_envar, arg[0]) != NULL)
	{
		squaredstr_free(arg);
		return (1);
	}
	squaredstr_free(arg);
	return (0);
}