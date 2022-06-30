/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_important_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:39:07 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/30 15:34:34 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	**join_double_pointer(char **str, char **ptr)
{
	char	**join;
	int		len[3];
	int		index;
	int		j;

	if (!ptr)
		return (str);
	index = -1;
	j = 0;
	len[0] = double_pointer_len(ptr);
	len[1] = double_pointer_len(ptr);
	len[2] = len[0] + len[1] + 1;
	join = (char **) malloc(len[2] * sizeof(char *));
	if (!join)
		return (NULL);
	while (index < len[2])
	{
		if (index < len[0])
			join[index] = str[index];
		else if (index >= len[1])
			join[index] = ptr[j++];
		index++;
	}
	return (join);
}

char	**join_args(t_node *head)
{
	t_args	*arg;
	char	**str;

	if (!head)
		return (NULL);
	str = ((t_args *) head->content)->after_expand;
	head = head->next;
	while (head != NULL)
	{
		arg = (t_args *) head->content;
		str = join_double_pointer(str, arg->after_expand);
		head = head->next;
	}
	return (str);
}

t_redirec	*get_output_input(t_node *head, int t)
{
	t_redirec	*redrec;
	t_redirec	*tmp;

	redrec = NULL;
	while (head != NULL)
	{
		tmp = (t_redirec *) head->content;
		if (t == 0 && (tmp->e_rtype == OUTPUT || tmp->e_rtype == APPEND))
			redrec = tmp;
		if (t == 1 && (tmp->e_rtype == INPUT || tmp->e_rtype == HERE_DOC))
			redrec = tmp;
		head = head->next;
	}
	return (redrec);
}
