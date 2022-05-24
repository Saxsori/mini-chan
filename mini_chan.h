/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_chan.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:40:03 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/24 20:55:51 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_CHAN_H
# define MINI_CHAN_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "./libft/libft.h"
# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"

typedef struct mini_tools
{
	int		opt_num;
	int		arg_num;
	int		arg_index;
	int		p_num;
	int		y_op;
	int		y_arg;
	char	*cwd;
	char	*getcwd_ret;
}	t_cmd_tools;

typedef struct mini_cmnd
{
	char		**split;
	char		*name;
	char		**option;
	char		**arguments;
	t_cmd_tools	tools;
}	t_mini_cmd;

typedef struct shell_chan
{
	char		*cmd_line;
	t_mini_cmd	*cmd_table;
	int			cmd_num;
	int			exit_status;
	char		**first_split;
}	t_shell_chan;

/******************* INITIALIZATION *******************/
void	init_shell_chan(t_shell_chan *main);
void	re_init_shell_chan(t_shell_chan *main);
void	init_mini_cmd(t_mini_cmd *cmd);

/*******************   CTRL & SIG   *******************/
void	ctrl_d(t_shell_chan *main);
void	ctrl_c(int c);
void	mini_sig(void);

/******************* MINI_TOOLS&CHECK *******************/
void	cmd_counter(t_shell_chan *main);
int		twstrlen(char	**tw_str);
void	mini_tools(t_shell_chan *main);
void	split_command(t_shell_chan *main);
int		is_command(char *cmd_name);

/******************* OPTIONS__PARSE *******************/
void	check_opt(t_mini_cmd *cmd);
int		is_there_opt(t_mini_cmd *cmd);
void	get_opt(t_mini_cmd *cmd);

/******************* ARGUMENTS_PARSE *******************/
void	check_arg(t_mini_cmd *cmd);
void	pre_arg(t_mini_cmd *cmd);
void	get_arg(t_mini_cmd *cmd);
int		is_there_arg(t_mini_cmd *cmd);

/******************* CMD_NAME_PARSE *******************/
int		command_name(t_shell_chan *main);
int		is_command(char *cmd_name);

/*******************  CMD_EXECUTE  *******************/
void	run_cmd(t_shell_chan *main);
void	which_command(t_shell_chan *main);

/*******************   MINI__CMD    *******************/
int		mini_cd(t_shell_chan *main);
int		mini_echo(t_shell_chan *main);
int		mini_pwd(t_shell_chan *main);
int		mini_exit(t_shell_chan *main);
int		mini_export(t_shell_chan *main);
int		mini_unset(t_shell_chan *main);
int		mini_env(t_shell_chan *main);

#endif
