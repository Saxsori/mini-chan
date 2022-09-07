  /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_chan.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 11:40:03 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/05 09:28:50 by aaljaber         ###   ########.fr       */
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
# include <sys/unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <valgrind/memcheck.h>
# include <sys/wait.h>
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

extern int		g_status;
typedef struct	shell_chan		t_shell_chan;
typedef struct	node			t_mini_envar;
typedef struct	expand_tools	t_expand_tools;
typedef struct echo_parse
{
	int	null_num;
	int	new_size;
}	t_mini_echo;

typedef struct node
{
	t_mini_envar	*prev;
	char			*env_name;
	char			*env_cont;
	char			*envar;
	int				declared;
	t_mini_envar	*next;
}	t_mini_envar;

typedef struct env_info
{
	t_expand_tools	*exp_tools;
	int				e_pos;
	int				e_index;
	int				e_valid;
	int				f_mode2_val;
	int				i_start;
	int				i_end;
	int				name_len;
	int				value_len;
	t_mini_envar	*env_ptr;
	char			*env_value;
}	t_env_info;

typedef struct expand_tools
{
	t_shell_chan	*main;
	int				index;
	int				env_num;
	int				i;
	int				pos;
	int				i_s;
	int				i_e;
	int				new_exp_len;
	t_env_info		*env_info;
}	t_expand_tools;

typedef struct p_quotes
{
	int		begin;
	int		end;
	int		first;
	int		second;
	int		q_string;
	// char	*line;
	int		exp_index;
}	t_mini_quotes;

typedef struct redirect_tools
{
	int				parse_err;
	int				num_arg;
	int				num_file;
	int				num_redir;
	int				num_part;
	int				i;
	int				k;
	int				j;
	int				**fd;
	int				fd_redir;
	int				ld;
	int				status;
	pid_t			child;
	int				*r_pos;
	char			**split;
	t_shell_chan	*main;
}	t_redir_tools;

typedef struct mini_redirecton
{
	char			*command;
	char			**arguments;
	char			**redir;
	char			**files;
	t_redir_tools	redir_tools;
}	t_mini_redir;

typedef struct p_redir
{
	int	num_redir;
	int	*r_valid;
	int	*r_index;
	int	begin;
	int	end;
	int	i_temp;
}	t_redir_parse;

typedef struct exe_tools
{
	int				arg_num;
	char			*cmd_name;
	char			**arguments;
	char			*err_command;
}	t_mini_exe_tools;

typedef struct mini_tools
{
	int				opt_num;
	int				arg_num;
	int				arg_index;
	int				p_num;
	int				y_op;
	int				y_arg;
	int				i_arg;
	int				new_arg;
	int				new_arg_size;
	char			*cwd_ret;
	char			*pwd;
	int				f_redir;
	pid_t			child;
	int				f_path;
	int				y_exe;
	int				y_redir;
	int				r_err_syn;
	DIR				*dir;
	t_redir_parse	p_redir;
	t_mini_envar	*envar;
}	t_cmd_tools;

typedef struct mini_cmnd
{
	char				**split;
	char				*name;
	char				**option;
	char				**arguments;
	char				*cmd_path;
	int					status;
	t_cmd_tools			tools;
	t_mini_redir		redir;
	t_shell_chan		*main;
	t_mini_exe_tools	exe_tools;
}	t_mini_cmd;

typedef struct pip_tools
{
	int		**fds;
	pid_t	*child;
	int		p_num;
	int		status;
	int		i;
	int		j;
}	t_mini_pipe;

typedef struct shell_chan
{
	char			*cmd_line;
	t_mini_quotes	q_pars;
	t_mini_cmd		*cmd_table;
	int				cmd_num;
	int				exit_status;
	char			**first_split;
	t_mini_envar	*head_envar;
	int				**exp_valid;
	int				**env_index;
	t_expand_tools	*exp_tools;
	int				d_rootpath;
	t_mini_echo		e_parse;
	t_mini_envar	*envar;
	char			*path;
	char			**path_split;
	int				f_pwd;
	t_mini_pipe		pipe_tools;
}	t_shell_chan;

/*******************     INITIALIZATION    *******************/
void			init_shell_chan(t_shell_chan *main);
void			re_init_shell_chan(t_shell_chan *main);
void			init_mini_cmd(t_mini_cmd *cmd, t_shell_chan *main);
void			init_mini_quotes(t_shell_chan *main, char *line);
void			init_expand_tools(t_expand_tools *exp_tools, \
												t_shell_chan *main, int index);
void			init_mem_cmd(t_mini_cmd *cmd);
void			init_mini_pipe(t_mini_pipe *p_tool);

/******************* MINI ERRORMNG & MEMNG *******************/
void			squaredstr_free(char **array);
void			squaredint_free(int **array, int len);
void			ft_exit(t_shell_chan *main, int	status);
void			free_mini_chan(t_shell_chan *main);
void			free_mini_envar(t_shell_chan *main);
void			free_shell_chan_mem(t_shell_chan *main);
void			free_ptr(void **ptr);

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
void			command_name(t_shell_chan *main);
int				is_command(char *cmd_name);
int				cmd_strncmp(const char *s1, const char *s2, int n);

/*******************      CMD_EXECUTE      *******************/

int				run_builtn(t_mini_cmd *cmd);
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

/***************** MINI_EXIT_TOOLS ***************************/

int				ft_scan_num(char *str);
int				check_long(char *str);
int				check_first_arg(t_mini_cmd *cmd);
void			exit_msg(t_shell_chan *main, char *status, char **msg);

/*******************      MINI__ENVAR      *******************/
void			create_envar_list(t_shell_chan *main, char **env);
t_mini_envar	*creat_first_node(t_mini_envar *head, char *data);
t_mini_envar	*add_node_at_end(t_mini_envar *head, char *data, char op);
void			add_env_data(t_mini_envar *temp, char *data);
void			del_mid_envar(t_mini_envar *envar);
t_mini_envar	*del_last_envar(t_mini_envar *head);
t_mini_envar	*del_first_envar(t_mini_envar *head);
t_mini_envar	*search_envar(t_mini_envar *head, char *env_name);
void			print_envar_list(t_mini_envar *head, char which);
void			envar_mode(t_mini_envar *temp, char op);

/*******************       MINI__ECHO      *******************/
int				is_extst(char *line);
void			parse_echo_case(t_shell_chan *main);
int				is_echo(char *line);
void			check_echo_opt(t_mini_cmd *cmd);
void			get_echo_arg_redir(t_mini_cmd *cmd);
int				is_echo_opt(char *line);
void			handle_one_case(t_mini_cmd *cmd);
char			**new_arg(t_mini_cmd *cmd);

/*******************      MINI_PWD_CD      *******************/
int				is_doubslash(char *line);
void			cd_home(t_mini_cmd *cmd, char *pwd);
void			change_oldpwd(t_mini_cmd *cmd, char *pwd);
void			change_pwd(t_mini_cmd *cmd, char *pwd);
void			check_root(t_mini_cmd *cmd);
void			change_dir(t_mini_cmd *cmd, char *cwd);

/*******************    MINI_QUOTE_PARSE   *******************/
int				is_closed(t_shell_chan *main, char *line, int index);
int				quotes_checker(t_shell_chan *main);
int				is_qt_valid(t_shell_chan *main, char *line);
int				quote_split(t_shell_chan *main, char *line, int i);
void			pre_quote(t_shell_chan *main);
int				line_len(char *line);
void			find_frst(t_shell_chan *main, char *line, int i);
void			find_scnd(t_shell_chan *main, char *line, int index, int i);
void			remove_quote(t_shell_chan *main);
void			tabbing_quote(t_shell_chan *main, char *line, int i);

/*******************    MINI_EXPAND_TOOLS   ******************/
void			expand_tools(t_shell_chan *main);
int				check_ignore_case(t_shell_chan *main, int i, int k, int num);
int				envar_num(t_shell_chan *main, int i);
void			find_env_index(t_shell_chan *main, int i);
void			expand_envar(t_shell_chan *main);
void			start_expand(t_expand_tools *exp_tools);
void			init_env_info(t_env_info *env_info, \
				t_expand_tools *exp_tools, int i);
void			find_istart(t_env_info *env_info);
void			get_env_value(t_env_info *env_info);
char			*get_env_name(t_env_info *env_info);
int				find_env(t_env_info *env_info);
void			find_name_size(t_env_info *env_info);
int				cmp_env_name(t_env_info *env_info, t_mini_envar *env);
void			handle_1dollar_case(t_env_info *env_info);
void			init_exp_loop(t_expand_tools *exp_tools);
void			two_dollar_case(char *line);

/*******************    MINI_REDIR_TOOLS   ******************/
void			redir_tools(t_shell_chan *main);
void			count_redir(t_mini_cmd *cmd, int i);
int				is_more_redir(char *line, int k);
void			check_redir(t_shell_chan *main, int i);
int				is_redir(char *line);
int				pre_redir(t_shell_chan *main);
void			redir_index(t_mini_cmd *cmd, int i);
void			init_loop_p_redir(t_mini_cmd *cmd, int i);
int				redir_pos(t_mini_cmd *cmd, int index);
int				last_redir(char *line, int i);
int				is_redir_index(t_mini_cmd *cmd, int index);
int				redir_err_syn(t_shell_chan *main);
void			redir_valid(t_shell_chan *main);
int				pre_redir(t_shell_chan *main);
void			take_v_redir(t_shell_chan *main);
void			num_valid_redir(t_mini_cmd *cmd);
int				is_there_v_redir(t_mini_cmd *cmd);
void			not_opp_redir(t_mini_cmd *cmd, char *line);
int				is_opp_redir(char *line, int index);
void			not_more_than_two(t_mini_cmd *cmd, char *line);
void			not_btwn_quote(t_mini_cmd *cmd, char *line);
void			is_btwn_quote(t_mini_cmd *cmd, char *line, int begin);
void			fill_redir_array(t_mini_cmd *cmd, char *line);
char			*get_redir(char *line, int begin, int end);
void			init_predir(t_redir_parse *p_redir);
void			init_predir_arrays(t_redir_parse *p_redir);
char			*replace_redir(char	*line, t_mini_cmd *cmd);
int				isvla_redir(t_mini_cmd *cmd, int index);
void			init_mini_redir(t_mini_redir *redir, t_shell_chan *main, int i);
void			split_redir(t_shell_chan *main);
int				check_redirline_syn(t_mini_redir *redir);
void			get_redir_pos(t_mini_redir *redir);
void			get_files(t_mini_redir *redir);
void			get_cmd(t_mini_redir *redir, int op);
void			get_arg_num(t_mini_redir *redir, int op);
void			get_redir_arg(t_mini_redir *redir, int op);
void			get_redir_part(t_mini_redir *redir, int op);
void			split_redir(t_shell_chan *main);
void			replace_tabbing_spaces(char	**split);
void			redir_heredoc_loop(t_mini_cmd *cmd);
void			redir_init_fd(t_mini_cmd *cmd);
void			redir_heredoc(t_mini_cmd *cmd);
void			redir_sign(t_mini_cmd *cmd, int i);
void			redir_append(t_mini_cmd *cmd, int i);
void			redir_out(t_mini_cmd *cmd, int i);
void			redir_in(t_mini_cmd *cmd, int i);
void			redir_exe(t_mini_cmd *cmd);

/*******************    MINI_REDIR_EXE   ******************/

void			redir_exe(t_mini_cmd *cmd);
void			redir(t_mini_cmd *cmd);

/*******************    MINI_EXPORT_TOOLS   ******************/
int				is_equal(char *line);
int				do_export(t_mini_cmd *cmd);
void			replace_envar(t_mini_cmd *cmd, int i);
int				isvalid_name(char *line);
int				check_is_name_there(t_shell_chan *main, char *line);
void			two_dollar_case(char *line);
void			do_expand(t_expand_tools *exp_tools);
void			do_unset(t_mini_cmd *cmd, int i);

/*******************    MINI_EXECUTE_TOOLS   ******************/
void			execute_tools(t_mini_cmd *cmd);
void			path(t_shell_chan *main, char *av[], int argc);
void			ft_pipe(t_shell_chan *main, char *av[], int ac);
void			path_test(t_shell_chan *main, char *av[],int ac);
void 			tst_redir(t_shell_chan *main, char *av[], int ac, int k);
void			tst_redir_main(t_shell_chan *main, char *av[], int ac);
// void			mini_execute(t_mini_cmd *cmd);
void			path_test(t_shell_chan *main, char *av[], int ac);
void			tst_redir(t_shell_chan *main, char *av[], int ac, int k);
void			tst_redir_main(t_shell_chan *main, char *av[], int ac);
void			get_path(t_shell_chan *main);
int				mini_execute(t_mini_cmd *cmd);

/*******************    MINI_EXECUTE_TOOLS(PIPES)   ******************/
void			mini_exe_pipe(t_shell_chan *main, int i);
void			pipe_tools(t_shell_chan *main);
void			init_fds(t_shell_chan *main);
void			path_finder(t_mini_cmd *cmd);
void			ft_dup_fds(t_shell_chan *main, int i);
void			ft_mini_pipe(t_shell_chan *main);

/*******************    MINI_EXIT  ******************/
void			pre_exit_arg(t_mini_cmd *cmd);

#endif