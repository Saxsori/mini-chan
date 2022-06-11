/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_quotes_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljaber <aaljaber@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:32:39 by aaljaber          #+#    #+#             */
/*   Updated: 2022/06/11 05:45:13 by aaljaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_chan.h"

int	env_which_index(t_shell_chan *main, int index, int i)
{
	int	k;

	k = -1;
	while (++k < envar_num(main, i))
	{
		if (main->env_index[i][k] == index)
			return (k);
	}
	return (-1);
}

/*
? 1- replace the first with \t and then search for the second quote to
? close the first and replace it with quote
? 2- between the first and the second quote replace all the spaces with \v
? this is the way to not split the spaces inside the quote by then
* in this function I check also the validity of exapnding "$" when it's inside
*	the quote if it was inside "" it won't lose it's validity if it was '' it will
*	which means it won't be expanded
* in case of $"" it shouldn't be expanded but it should print what's inside the quote
* 0 - invalid expansion
* 1 - valid expansion
* 2 - prints what inside the quote Without $
? for the case of $"" i Will recieve the quote and the index of the quote 
? which is 1 so to check if this is #2 expansion case I should check the previous index
? if it was $ then this is invalid expansion and I will put 2 on it's exp_valid pos
*/
void	find_scnd(t_shell_chan *main, char *line, int index, int i)
{
	char			quote;

	quote = line[index];
	line[index] = '\t';
	if (line[index - 1] == '$')
		main->exp_valid[i][env_which_index(main, index - 1, i)] = 2;
	while (++index < ft_strlen(line) + 1)
	{
		if (line[index] == '$')
		{
			if (quote == 34)
				main->exp_valid[i][env_which_index(main, index, i)] = 1;
			else if (quote == 39)
				main->exp_valid[i][env_which_index(main, index, i)] = 0;
			main->q_pars.exp_index++;
		}
		if (line[index] == ' ')
			line[index] = '\v';
		if (line[index] == quote)
		{
			line[index] = '\t';
			main->q_pars.begin = index;
			return ;
		}
	}
}

/*
? hold the first quote and send the line with the index to look
? 	for the second quote
*/
void	find_frst(t_shell_chan *main, char *line, int i)
{
	while (++main->q_pars.begin < ft_strlen(line))
	{
		if (line[main->q_pars.begin] == 34 || line[main->q_pars.begin] == 39)
			find_scnd(main, line, main->q_pars.begin, i);
	}
}

/*
line length with no quotes
? count the length of the string without the closed quote
*/
int	line_len(char *line)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (++i < ft_strlen(line))
	{
		if (line[i] != '\t')
			len++;
	}
	return (len);
}

/*
after checking of the quotes are valid (closed) then take them off
	and store the new one withput the quote
? 1- find first quote and from there find the second one
? 2- malloc with the new size
? 3- copy everything (the line without quotes)
?	in the string except the \t (the quote)
? 4- free the line from the first split which hold the 
?	old string
? 5- copy the new line without the quote in the first split string
? 6- free the new line
	// printf("%s - %d\n", main->first_split[i], ft_strlen(main->first_split[i]));
*/
int	quote_split(t_shell_chan *main, char *line, int i)
{
	char	*new_line;
	int		f;
	int		n;

	find_frst(main, line, i);
	new_line = (char *)malloc((line_len(line) + 1) * sizeof(char));
	f = -1;
	n = 0;
	while (++f < ft_strlen(line))
	{
		if (line[f] != '\t')
			new_line[n++] = line[f];
	}
	new_line[n] = '\0';
	free(main->first_split[i]);
	main->first_split[i] = ft_strdup(new_line);
	free(new_line);
	n = -1;
	while (++n < envar_num(main, i))
	{
		if (main->exp_valid[i][n] == -1)
			main->exp_valid[i][n] = 1;
	}
	n = -1;
	while (++n < envar_num(main, i))
		printf("ind%d valid%d \n", main->env_index[i][n], main->exp_valid[i][n]);
	return (1);
}
