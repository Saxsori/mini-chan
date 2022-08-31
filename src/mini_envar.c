/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_envar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:22:48 by aaljaber          #+#    #+#             */
/*   Updated: 2022/08/30 22:47:49 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

void	get_pwd_envar(t_shell_chan *main)
{
	t_mini_envar	*envar;
	char			*pwd;

	pwd = (char *)malloc(1024 * sizeof(char));
	envar = search_envar(main->head_envar, "PWD");
	free(envar->env_cont);
	getcwd(pwd, 1024);
	envar->env_cont = ft_strdup(pwd);
	free(pwd);
	envar = search_envar(main->head_envar, "OLDPWD");
	if (envar)
	{
		if (envar->prev == NULL)
			main->head_envar = del_first_envar(main->head_envar);
		else if (envar->next == NULL)
			main->head_envar = del_last_envar(main->head_envar);
		else
			del_mid_envar(envar);
		add_node_at_end(main->head_envar, "OLDPWD", 'x');
	}
}

/*
? the main function to create the list
? creating the first node and add the first env
? adding the other env in loop
	// print_envar_list(main->head_envar);
*/
void	create_envar_list(t_shell_chan *main, char **env)
{
	int	i;

	main->head_envar = creat_first_node(main->head_envar, env[0]);
	i = 0;
	while (env[++i])
		main->head_envar = add_node_at_end(main->head_envar, env[i], 'n');
	get_pwd_envar(main);
}

/*
head here is just a pointer that will point to the first node of the
 list so passing that pointer ..
? 1- malloc a temp pointer on the size of one node
? 2- passing null to the pointer of the prev and next pointer
?	since there it's the first node created
? 3- passing the pointer of temp to head so that head can point to the first 
?	node created which is the head of the list
? 4- return head to the head pointer in the main function
*/
t_mini_envar	*creat_first_node(t_mini_envar *head, char *data)
{
	t_mini_envar	*temp;

	temp = (t_mini_envar *)malloc(sizeof(t_mini_envar));
	temp->prev = NULL;
	temp->next = NULL;
	temp->env_cont = NULL;
	temp->env_name = NULL;
	temp->envar = NULL;
	add_env_data(temp, data);
	head = temp;
	return (head);
}