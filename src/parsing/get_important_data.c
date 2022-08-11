/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_important_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:39:07 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 18:12:39 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**join_args(t_node *head)
{
	t_args	*arg;
	char	**str;

	if (!head)
		return (NULL);
	str = ft_strdup_double(((t_args *) head->content)->after_expand);
	head = head->next;
	while (head != NULL)
	{
		arg = (t_args *) head->content;
		str = join_double_pointer(str, ft_strdup_double(arg->after_expand));
		head = head->next;
	}
	return (str);
}

t_redirec	*get_input(t_node *head)
{
	t_redirec	*redrec;
	t_redirec	*tmp;
	int			last_fd;

	redrec = NULL;
	last_fd = 0;
	while (head != NULL)
	{
		tmp = (t_redirec *) head->content;
		if (tmp->e_rtype == INPUT || tmp->e_rtype == HERE_DOC)
		{
			if (last_fd != 0)
				close(last_fd);
			last_fd = tmp->fd;
			redrec = tmp;
		}
		head = head->next;
	}
	return (redrec);
}

t_redirec	*get_output(t_node *head)
{
	t_redirec	*redrec;
	t_redirec	*tmp;
	int			last_fd;

	redrec = NULL;
	last_fd = 1;
	while (head != NULL)
	{
		tmp = (t_redirec *) head->content;
		if (tmp->e_rtype == OUTPUT || tmp->e_rtype == APPEND)
		{
			if (last_fd != 1)
				close(last_fd);
			last_fd = tmp->fd;
			redrec = tmp;
		}
		head = head->next;
	}
	return (redrec);
}
