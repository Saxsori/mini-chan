/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_envar_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:53:10 by aaljaber          #+#    #+#             */
/*   Updated: 2022/09/14 12:26:21 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

/*
to search for a specific env so it will take the name and the head of the list
? 1- passing the head into a temp var (envar)
? 2- check the head if it was what we are looking for
? 2- else check if the next is not NULL "not only one node"
?	so then check the env name if it was the same as what we are looking for
? 3- if next was NULL then we are on the last node 
?	so check the env name on this node
? 4- else return NULL cuz env_name not found
*/
t_mini_envar	*search_envar(t_mini_envar *head, char *env_name)
{
	t_mini_envar	*envar;

	envar = head;
	if (!ft_strncmp(envar->env_name, env_name, ft_strlen(envar->env_name)))
		return (envar);
	if (envar->next && !envar->prev)
	{
		while (envar->next)
		{
			if (!ft_strncmp(envar->env_name, env_name, \
													ft_strlen(envar->env_name)))
				return (envar);
			else
				envar = envar->next;
		}
		if (!ft_strncmp(envar->env_name, env_name, ft_strlen(envar->env_name)))
			return (envar);
	}
	return (NULL);
}

/*
-> to print the content of the list
? taking the pointer of the head into a temp pointer 
? if it was not NULL then moving form the next pointer of the head till 
? the end of the list and print the content
*/
void	print_envar_list(t_mini_envar *head, char which)
{
	t_mini_envar	*print;

	print = head;
	while (print != NULL)
	{
		if (which == 'n')
		{
			if (print->declared)
				printf(BCYN"%s=%s\n"BWHT, print->env_name, print->env_cont);
		}
		if (which == 'x')
		{
			if (print->env_cont[0] != '\0')
				printf(BCYN"declare -x %s=\"%s\"\n"BWHT, \
							print->env_name, print->env_cont);
			else
				printf(BCYN"declare -x %s\n"BWHT, print->env_name);
		}
		print = print->next;
	}
}
