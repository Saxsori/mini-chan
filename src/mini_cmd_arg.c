
#include "../mini_chan.h"

/*
? 1- calc how many parts (string) in the 
?	cmd->split (splitting parts from spaces)
? 2- to know how many arguments = 
?	num of parts - the index from where the arg is starting
? 3- malloc the 2d array of arguments depending on how many numbers of args
? 4- malloc each array depending on the size of each array using strlen
?	NOTE that where taking the size of ech array from the parts that we split in
?	cmd->split .. so it shpuld start from the index from where arg is begin
*/
void	pre_arg(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	i = -1;
	k = cmd->tools.arg_index;
	cmd->tools.p_num = twstrlen(cmd->split);
	cmd->tools.arg_num = cmd->tools.p_num - cmd->tools.arg_index;
	cmd->arguments = (char **)malloc(cmd->tools.arg_num * sizeof(char *));
	while (++i < cmd->tools.arg_num)
		cmd->arguments[i] = (char *)malloc(ft_strlen(cmd->split[k++]));
}

/*
? 1- prepare the cmd->arguments by calculating 
?	how many arg and malloc depending on that
? 2- fill the arg's 2d array
?	getting the arguments from the split starting
?	drom where the args is starting using arg_index
! check when it's only one arg 
*/
void	get_arg(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	pre_arg(cmd);
	k = cmd->tools.arg_index;
	i = -1;
	while (++i < cmd->tools.arg_num)
		cmd->arguments[i] = cmd->split[k--];
}

/* 
! check if they may pass 
! cmd -op arg -arg
! check if arg_index is correct
*/
int	is_there_arg(t_mini_cmd *cmd)
{
	int	i;
	int	k;

	i = -1;
	k = -1;
	while (cmd->split[++i])
	{
		k = -1;
		while (cmd->split[i][++k])
		{
			if (cmd->split[i][k] == '-')
			{
				i++;
				k = -1;
				cmd->tools.y_op = 1;
			}
		}
		if (cmd->tools.y_op)
			cmd->tools.y_op = 0;
		else
		{
			cmd->tools.arg_index = i;
			break ;
		}
	}
	return (cmd->tools.arg_index);
}

void	check_arg(t_mini_cmd *cmd)
{
	if (is_there_arg(cmd) != -1)
		get_arg(cmd);
	else
		cmd->arguments = NULL;
}
