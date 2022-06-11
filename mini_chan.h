/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_chan.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:40:03 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/11 11:16:00 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_CHAN_H
# define MINI_CHAN_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
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

typedef struct env_expand
{
	t_shell_chan	*main;
	int				index;
	int				env_num;
	int				env_ord;
	int				start;
	int				end;
	int				name_len;
	t_mini_envar	*env_ptr;
	int				new_len_exp;
	int				s;
	int				e;
	int				i;
	int				l;
}	t_env_expand;

typedef struct p_quotes
{
	int		begin;
	int		end;
	int		first;
	int		second;
	int		q_string;
	char	*line;
	int		exp_index;
}	t_mini_quotes;

typedef struct node
{
	t_mini_envar	*prev;
	char			*env_name;
	char			*env_cont;
	char			*envar;
	int				hidden;
	int				declared;
	t_mini_envar	*next;
}	t_mini_envar;

typedef struct mini_tools
{
	int				opt_num;
	int				arg_num;
	int				arg_index;
	int				p_num;
	int				y_op;
	int				y_arg;
	char			*cwd_ret;
	char			*pwd;
	DIR				*dir;
	t_mini_envar	*envar;
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
	t_mini_quotes	q_pars;
	t_mini_cmd		*cmd_table;
	int				cmd_num;
	int				exit_status;
	char			**first_split;
	t_mini_envar	*head_envar;
	int				d_rootpath;
	int				**exp_valid;
	int				**env_index;
}	t_shell_chan;

/*******************     INITIALIZATION    *******************/
void			init_shell_chan(t_shell_chan *main);
void			re_init_shell_chan(t_shell_chan *main);
void			init_mini_cmd(t_mini_cmd *cmd, t_shell_chan *main);
void			init_mini_quotes(t_shell_chan *main, char *line);
void			init_env_expand(t_env_expand *env_exp, \
												t_shell_chan *main, int index);
void			re_init_env_expand(t_env_expand *exp_tools);

/*******************      CTRL & SIG       *******************/
void			ctrl_d(t_shell_chan *main);
void			ctrl_c(int c);
void			mini_sig(void);

/*******************   MINI__TOOLS&CHECK   *******************/
void			first_cmd_split(t_shell_chan *main);
int				twstrlen(char	**tw_str);
void			cmd_counter(t_shell_chan *main);
void			split_command(t_shell_chan *main);
void			new_prompt(int i);
int				check_cmd_line(char *line);

/*******************    OPTIONS___PARSE    *******************/
void			check_opt(t_mini_cmd *cmd);
int				is_there_opt(t_mini_cmd *cmd);
void			get_opt(t_mini_cmd *cmd);

/*******************    ARGUMENTS_PARSE    *******************/
void			check_arg(t_mini_cmd *cmd);
int				is_there_arg(t_mini_cmd *cmd);
void			pre_arg(t_mini_cmd *cmd);
void			get_arg(t_mini_cmd *cmd);

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
int				mini_chan(void);

/******************* MINI ERRORMNG & MEMNG *******************/
void			squaredstr_free(char **array);
void			squaredint_free(int **array, int len);

/*******************      MINI__ENVAR      *******************/

void			create_envar_list(t_shell_chan *main, char **env);
t_mini_envar	*creat_first_node(t_mini_envar *head, char *data);
t_mini_envar	*add_node_at_end(t_mini_envar *head, char *data, char op);
void			add_env_data(t_mini_envar *temp, char *data);
void			del_mid_envar(t_mini_envar *envar);
t_mini_envar	*del_last_envar(t_mini_envar *head);
t_mini_envar	*del_first_envar(t_mini_envar *head);
t_mini_envar	*sreach_envar(t_mini_envar *head, char *env_name);
void			print_envar_list(t_mini_envar *head, char which);
void			add_hid_env_data(t_mini_envar *temp, char *data);
void			add_hid_env(t_shell_chan *main);
void			envar_mode(t_mini_envar *temp, char op);

/*******************       MINI__ECHO      *******************/
int				is_extst(char *line);
void			check_echo_opt(t_mini_cmd *cmd);
int				is_echo_opt(char **opt, char which, int len);

/*******************      MINI_PWD_CD      *******************/
int				is_doubslash(char *line);

/*******************    MINI_QUOTE_PARSE   *******************/
int				is_closed(t_shell_chan *main, char *line, int index);
int				quotes_checker(t_shell_chan *main);
int				is_qt_valid(t_shell_chan *main, char *line);
int				quote_split(t_shell_chan *main, char *line, int i);
int				line_len(char *line);
void			find_frst(t_shell_chan *main, char *line, int i);
void			find_scnd(t_shell_chan *main, char *line, int index, int i);

/*******************    MINI_EXPAND_TOOLS   ******************/
void			expand_tools(t_shell_chan *main);
int				envar_num(t_shell_chan *main, int i);
void			expand_envar(t_shell_chan *main);
void			strat_expand(t_env_expand *exp_tools);
int				is_envar(t_env_expand *exp_tools, int i);
int				find_env(t_env_expand *exp_tools);
int				cmp_env_name(t_env_expand *exp_tools, t_mini_envar *env);
void			find_name_size(t_env_expand *exp_tools);
int				is_exp_valid(t_env_expand *exp_tools);
int				is_there_envar(char *line);
void			do_expand(t_env_expand *expand_tools);
#endif
