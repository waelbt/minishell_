/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:03:48 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 19:14:49 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_qoutes_delimiter(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		tmp = str[i];
		str[i] = get_value(str[i]);
		free(tmp);
		i++;
	}	
}

void	open_all_redrec(t_node **command)
{
	t_node	*temporary;
	t_cmd	*cmd;

	temporary = *command;
	while (temporary != NULL)
	{
		cmd = (t_cmd *)temporary->content;
		if (!open_file_descriptor(&cmd->redrec))
			cmd->e_rtype = NOT_VALID;
		cmd->input = get_input(cmd->redrec);
		cmd->output = get_output(cmd->redrec);
		temporary = temporary->next;
	}
}

void	sig_handler(int sig)
{
	(void) sig;
	ft_setter(1);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
