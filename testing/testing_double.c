/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 00:37:42 by aaljaber          #+#    #+#             */
/*   Updated: 2022/07/20 16:52:25 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"
// t_mini_envar	*search_envar(t_mini_envar *head, char *env_name)
// {
// 	t_mini_envar	*envar;

// 	envar = head;
// 	if (envar->next && !envar->prev)
// 	{
// 		while (envar->next)
// 		{
// 			if (!ft_strncmp(envar->env_name, env_name, ft_strlen(envar->env_name)))
// 				return (envar);
// 			else
// 				envar = envar->next;
// 		}
// 		if (!ft_strncmp(envar->env_name, env_name, ft_strlen(envar->env_name)))
// 			return (envar);
// 	}
// 	else
// 	{
// 		if (!ft_strncmp(envar->env_name, env_name, ft_strlen(envar->env_name)))
// 			return (envar);
// 	}
// 	return (NULL);
// }

// void	print_envar_list(t_mini_envar *head)
// {
// 	t_mini_envar	*print;

// 	print = head;
// 	while (print != NULL)
// 	{
// 		printf(BCYN"%s=%s\n"BWHT, print->env_name, print->env_cont);
// 		print = print->next;
// 	}
// }

// int	twstrlen(char **tw_str)
// {
// 	int	i;

// 	i = 0;
// 	while (tw_str[i])
// 		i++;
// 	return (i);
// }

// void	add_env_data(t_mini_envar *temp, char *data)
// {
// 	char	**split;
// 	int		i;

// 	i = 1;
// 	split = ft_split(data, '=');
// 	temp->env_name = ft_strdup(split[0]);
// 	if (twstrlen(split) <= 2)
// 	{
// 		if (split[1] != NULL)
// 			temp->env_cont = ft_strdup(split[1]);
// 		else
// 			temp->env_cont = NULL;
// 	}
// 	if (twstrlen(split) > 2)
// 	{
// 		while (++i < twstrlen(split))
// 			temp->env_cont = ft_strjoin(temp->env_cont, split[i]);
// 	}
// 	squaredstr_free(split);
// }

// t_mini_envar	*creat_first_node(t_mini_envar *head, char *data)
// {
// 	t_mini_envar	*temp;

// 	temp = (t_mini_envar *)malloc(sizeof(t_mini_envar));
// 	temp->prev = NULL;
// 	temp->next = NULL;
// 	add_env_data(temp, data, 'n');
// 	head = temp;
// 	return (head);
// }

// t_mini_envar	*add_node_at_end(t_mini_envar *head, char *data, char op)
// {
// 	t_mini_envar	*temp;
// 	t_mini_envar	*traversal;

// 	temp = (t_mini_envar *)malloc(sizeof(t_mini_envar));
// 	temp->prev = NULL;
// 	temp->next = NULL;
// 	add_env_data(temp, data);
// 	traversal = head;
// 	while (traversal->next != NULL)
// 		traversal = traversal->next;
// 	traversal->next = temp;
// 	temp->prev = traversal;
// 	return (head);
// }

// void	create_envar_list(t_shell_chan *main, char **env)
// {
// 	int	i;

// 	main->head_envar = creat_first_node(main->head_envar, env[0]);
// 	i = 0;
// 	while (env[++i])
// 		main->head_envar = add_node_at_end(main->head_envar, env[i]);
// }

// t_mini_envar	*del_first_envar(t_mini_envar *head)
// {
// 	head = head->next;
// 	free(head->prev);
// 	head->prev = NULL;
// 	return (head);
// }

// t_mini_envar	*del_last_envar(t_mini_envar *head)
// {
// 	t_mini_envar	*temp;
// 	t_mini_envar	*traversal;

// 	traversal = head;
// 	while (traversal->next != NULL)
// 		traversal = traversal->next;
// 	temp = traversal->prev;
// 	temp->next = NULL;
// 	free(traversal);
// 	return (head);
// }

// void	del_mid_envar(t_mini_envar *envar)
// {
// 	t_mini_envar	*temp;

// 	temp = envar->prev;
// 	temp->next = envar->next;
// 	envar->next->prev = temp;
// 	free (envar);
// 	envar = NULL;
// }

int main (int argc, char **argv, char **env)
{
	t_shell_chan	main;
	// t_mini_envar	*enva;

	(void) argc;
	(void) argv;
	create_envar_list(&main, env);
	// print_envar_list(main.head_envar);
	// path(&main,argv,argc);
	// ft_pipe(&main,argv,argc);
	path_test(&main, argv, argc);
	// enva = search_envar(main.head_envar, "SHELL");
	// main.head_envar = dl_first_envar(main.head_envar);
	// main.head_envar = del_last_envar(main.head_envar);
	// printf(BGRN"----------------\n");
	// del_mid_envar(enva);
	// print_envar_list(main.head_envar);
	// printf(BGRN"%s=%s\n"BWHT, enva->env_name, enva->env_cont);
	return (0);
}
//    char *pathvar;

//    pathvar = getenv("PATH");
//    printf("pathvar=%s",pathvar);

