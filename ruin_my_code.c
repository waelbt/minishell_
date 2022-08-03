/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruin_my_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:48:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/02 17:51:02 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/include/minishell.h"

void	*fill_her_doc_in_fork(t_node **head, char **envp)
{
	t_node		*temporary;
	t_redirec	*redrec;
	int			status;
	int			id;

	id = fork();
	if (id != 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(id, &status, 0);
		if(WIFEXITED(status))
			open_here_doc(head);
		if(WIFSIGNALED(status))
		{
			signal(SIGINT, sig_handler);
			return (NULL);
		}
	}
	else
	{
		temporary = *head;
		while (temporary != NULL)
		{
			redrec = (t_redirec *) temporary->content;
			if(redrec->e_rtype == 3)
				here_doc(redrec, envp);
			temporary = temporary->next;
		}
		exit(0);
	}
	return ((void *)1);
}

void	*open_file_descriptor(t_node **head)
{
	t_node		*temporary;
	t_redirec	*redrec;

	temporary = *head;

	while (temporary != NULL)
	{
		redrec = (t_redirec *) temporary->content;
		if (redrec->e_rtype == INPUT)
			redrec->fd = open(redrec->after_expand[0], O_RDONLY, 0666);
		else if (redrec->e_rtype == OUTPUT)
			redrec->fd = open(redrec->after_expand[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (redrec->e_rtype == APPEND)
			redrec->fd = open(redrec->after_expand[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
		else if (redrec->e_rtype == HERE_DOC)
			redrec->fd = open(redrec->path, O_RDONLY, 0666);
		if(redrec->fd < 0)
		{
			ft_setter(1);
			printf_error("minishell: no such file or directory: ", redrec->after_expand[0], "\n");
			return (NULL);
		}
		temporary = temporary->next;
	}
	return ((void *)1);
}
