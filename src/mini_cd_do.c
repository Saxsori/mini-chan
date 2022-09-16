/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:14 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/16 05:18:47 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	cd_home(t_mini_cmd *cmd)
{
	cmd->tools.envar = search_envar(cmd->main->head_envar, "HOME");
	if (cmd->tools.envar)
	{
		chdir(cmd->tools.envar->env_cont);
		update_cd_envars(cmd);
		return (0);
	}
	else
		errmsg("cd", "HOME not set");
	return (1);
}

void	no_parent_dir(t_mini_cmd *cmd)
{
	char	*temp;

	change_oldpwd(cmd);
	errmsg(NULL, GETCWD_ERR);
	cmd->tools.envar = search_envar(cmd->main->head_envar, "PWD");
	temp = ft_strjoin(cmd->tools.envar->env_cont, "/..");
	free (cmd->tools.envar->env_cont);
	cmd->tools.envar->env_cont = ft_strdup(temp);
	cmd->tools.envar = NULL;
	free(temp);
}

int	change_dir(t_mini_cmd *cmd)
{
	int		ret;
	char	*pwd;

	ret = chdir(cmd->arguments[0]);
	if (ret == -1)
	{
		errmsg(cmd->name, strerror(errno));
		return (1);
	}
	else
	{
		pwd = getcwd(NULL, 1024);
		if (!pwd)
			no_parent_dir(cmd);
		else
			update_cd_envars(cmd);
	}
	return (0);
}