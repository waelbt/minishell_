/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:01:52 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/30 10:57:38 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern struct vars vr;

void	here_doc(t_redirec *redirc, char **envp)
{
	int			fd;
	char		*str;

	signal(SIGINT, SIG_DFL);
	fd = open(redirc->path, O_RDWR | O_CREAT, 0666);
	if (fd < 0)
		return ;
	write(1, ">", 1);
	str = readline("\033[0;35> \033[0;37m");
	while (str && ft_strcmp(str, redirc->after_expand[0]))
	{
		if (!ft_strchr(redirc->file, '\'')
			&& !ft_strchr(redirc->file, '"'))
				str = pure_arg(str, envp);
			write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		write(1, ">", 1);
		str = readline("\033[0;35> \033[0;37m");
	}
	if(str)
		free(str);
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
