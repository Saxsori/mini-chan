/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_do.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 04:31:14 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/31 21:01:19 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	change_pwd(t_mini_cmd *cmd, char *pwd)
{
	getcwd(pwd, 1024);
	cmd->tools.envar = search_envar(cmd->main->head_envar, "PWD");
	if (cmd->tools.envar)
	{
		free(cmd->tools.envar->env_cont);
		if (cmd->main->d_rootpath)
			cmd->tools.envar->env_cont = ft_strjoin("/", pwd);
		else
			cmd->tools.envar->env_cont = ft_strdup(pwd);
	}
}

void	change_oldpwd(t_mini_cmd *cmd, char *pwd)
{
	char	*data;

	if (check_is_name_there(cmd->main, "OLDPWD"))
	{
		cmd->tools.envar = search_envar(cmd->main->head_envar, "OLDPWD");
		free(cmd->tools.envar->env_cont);
		cmd->tools.envar->env_cont = ft_strdup(pwd);
		cmd->tools.envar->declared = 1;
	}
	else
	{
		data = ft_strjoin("OLDPWD=", pwd);
		add_node_at_end(cmd->main->head_envar, data, 'n');
	}
}

void	cd_home(t_mini_cmd *cmd, char *pwd)
{
	cmd->tools.envar = search_envar(cmd->main->head_envar, "HOME");
	chdir(cmd->tools.envar->env_cont);
	change_oldpwd(cmd, pwd);
	change_pwd(cmd, pwd);
}

void	change_cwd(t_mini_cmd *cmd, char *cwd)
{
	if (cmd->tools.envar)
	{
		check_root(cmd);
		change_oldpwd(cmd, cwd);
		change_pwd(cmd, cwd);
	}
	else
	{
		if (cmd->main->f_pwd)
		{
			cmd->main->f_pwd = 0;
			cmd->tools.envar = search_envar(cmd->main->head_envar, "OLDPWD");
			if (!cmd->tools.envar->declared)
				cmd->tools.envar->declared = 1;
			free(cmd->tools.envar->env_cont);
			cmd->tools.envar->env_cont = malloc(sizeof(char));
			cmd->tools.envar->env_cont[0] = '\0';
		}
		else
			change_oldpwd(cmd, cwd);
	}
}

void	change_dir(t_mini_cmd *cmd, char *cwd)
{
	char		*pwd;
	char		*temp;

	pwd = getcwd(NULL, 1024);
	cmd->tools.envar = search_envar(cmd->main->head_envar, "PWD");
	printf("cwd %s\n", pwd);
	if (!pwd)
	{
		printf(BRED"cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n"BWHT);
		temp = ft_strjoin(cmd->tools.envar->env_cont, "/..");
		free (cmd->tools.envar->env_cont);
		cmd->tools.envar->env_cont = ft_strdup(pwd);
		free (temp);
	}
	else
		change_cwd(cmd, cwd);
}
