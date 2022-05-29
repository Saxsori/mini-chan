/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_chan.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:40:03 by aaljaber          #+#    #+#             */
/*   Updated: 2022/05/28 23:19:31 by aaljaber         ###   ########.fr       */
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
# define BPUR "\e[0;35m"

typedef struct shell_chan	t_shell_chan;
typedef struct node			t_mini_envar;

typedef struct node
{
	t_mini_envar	*prev;
	char			*env_name;
	char			*env_cont;
	char			*envar;
	t_mini_envar	*next;
}	t_mini_envar;

typedef struct mini_tools
{
	int		opt_num;
	int		arg_num;
	int		arg_index;
	int		p_num;
	int		y_op;
	int		y_arg;
	char	*cwd_ret;
	char	*pwd;
}	t_cmd_tools;

typedef struct mini_cmnd
{
	char			**split;
	char			*name;
	char			**option;
	char			**arguments;
	t_cmd_tools		tools;
	t_shell_chan	*main;
}	t_mini_cmd;

typedef struct shell_chan
{
	char			*cmd_line;
	t_mini_cmd		*cmd_table;
	int				cmd_num;
	int				exit_status;
	char			**first_split;
	t_mini_envar	*head_envar;
}	t_shell_chan;


/*******************     INITIALIZATION    *******************/
void			init_shell_chan(t_shell_chan *main);
void			re_init_shell_chan(t_shell_chan *main);
void			init_mini_cmd(t_mini_cmd *cmd, t_shell_chan *main);

/*******************      CTRL & SIG       *******************/
void			ctrl_d(t_shell_chan *main);
void			ctrl_c(int c);
void			mini_sig(void);

/*******************   MINI__TOOLS&CHECK   *******************/
void			cmd_counter(t_shell_chan *main);
int				twstrlen(char	**tw_str);
void			mini_tools(t_shell_chan *main);
void			split_command(t_shell_chan *main);
int				is_command(char *cmd_name);

/*******************    OPTIONS___PARSE    *******************/
void			check_opt(t_mini_cmd *cmd);
int				is_there_opt(t_mini_cmd *cmd);
void			get_opt(t_mini_cmd *cmd);

/*******************    ARGUMENTS_PARSE    *******************/
void			check_arg(t_mini_cmd *cmd);
void			pre_arg(t_mini_cmd *cmd);
void			get_arg(t_mini_cmd *cmd);
int				is_there_arg(t_mini_cmd *cmd);

/*******************    CMD__NAME_PARSE    *******************/
int				command_name(t_shell_chan *main);
int				is_command(char *cmd_name);

/*******************      CMD_EXECUTE      *******************/
int				run_cmd(t_shell_chan *main);
int				which_command(t_mini_cmd *cmd);

/*******************       MINI_CMD        *******************/
int				mini_cd(t_mini_cmd *cmd);
int				mini_echo(t_mini_cmd *cmd);
int				mini_pwd(t_mini_cmd *cmd);
int				mini_exit(t_mini_cmd *cmd);
int				mini_export(t_mini_cmd *cmd);
int				mini_unset(t_mini_cmd *cmd);
int				mini_env(t_mini_cmd *cmd);

/******************* MINI ERRORMNG & MEMNG *******************/
void			sequared_free(char **array);

/*******************      MINI__ENVAR      *******************/

void			create_envar_list(t_shell_chan *main, char **env);
t_mini_envar	*creat_first_node(t_mini_envar *head, char *data);
t_mini_envar	*add_node_at_end(t_mini_envar *head, char *data);
void			add_env_data(t_mini_envar *temp, char *data);
void			print_envar_list(t_mini_envar *head);
t_mini_envar	*sreach_envar(t_mini_envar *head, char *env_name);
void			del_mid_envar(t_mini_envar *envar);
t_mini_envar	*del_last_envar(t_mini_envar *head);
t_mini_envar	*del_first_envar(t_mini_envar *head);
#endif
