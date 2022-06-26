/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_important_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:01:11 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/25 18:46:40 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	check_eof(t_node *head)
{
	t_args	*args;

	while (head != NULL)
	{
		args = (t_args *) head->content;
		if (args->value[0] == '\0')
			return (0);
		head = head->next;
	}
	return (1);
}

char	*join_args(t_node *head)
{
	t_args	*arg;
	char	*str;
	char	*tmp;

	if (!head)
		return (NULL);
	str = ft_strdup(((t_args *) head->content)->value);
	head = head->next;
	while (head != NULL)
	{
		arg = (t_args *) head->content;
		tmp = str;
		str = ft_strjoin(str, " ");
		free(tmp);
		tmp = str;
		str = ft_strjoin(str, arg->value);
		free(tmp);
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

void	ft_unlik(int *index)
{
	char	*tmp[2];

	while (*index > -1)
	{
		tmp[0] = ft_itoa(*index);
		tmp[1] = ft_strjoin("/var/TMP/her_doc", tmp[0]);
		unlink(tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		(*index)--;
	}
	*index = 0;
}

char	**ft_spilt_beta(t_node *args)
{
	char	*str;
	char	**ptr;
	t_args	*arg;
	int		i;

	i = 0;
	if (check_eof(args))
	{
		str = join_args(args);
		ptr = ft_split(str, 32);
		free(str);
	}
	else
	{
		ptr = malloc(sizeof(char *) * (ft_lstsize(args) + 1));
		while (args)
		{
			arg = (t_args *) args->content;
			ptr[i] = ft_strdup(arg->value);
			args = args->next;
			i++;
		}
		ptr[i] = NULL;
	}
	return (ptr);
}
