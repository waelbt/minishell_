/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:01:52 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/29 19:35:37 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	here_doc(t_redirec *redirc, char **envp, int *index, int *fd)
{
	char		*str[4];

	str[1] = ft_itoa(*index);
	str[2] = ft_strjoin("/var/TMP/her_doc", str[1]);
	str[3] = NULL;
	*fd = open(str[2], O_RDWR | O_CREAT, 0666);
	if (*fd < 0)
		return ;
	(*index)++;
	write(1, ">", 1);
	str[0] = readline("\033[0;35> \033[0;37m");
	while (ft_strcmp(str[0], redirc->after_expand[0]))
	{
		if (!ft_strchr(redirc->file, '\'')
			&& !ft_strchr(redirc->file, '"'))
			str[0] = pure_arg(str[0], envp);
		write(*fd, str[0], ft_strlen(str[0]));
		write(*fd, "\n", 1);
		free(str[0]);
		write(1, ">", 1);
		str[0] = readline("\033[0;35> \033[0;37m");
	}
	close(*fd);
	*fd = open(str[2], O_RDWR | O_CREAT, 0666);
	free_double_char(str, 1);
}

int	open_file_descriptor(t_redirec	*redrec, char **envp, int *index)
{
	int	fd;

	if (redrec->e_rtype == INPUT)
		fd = open(redrec->after_expand[0], O_RDWR, 0666);
	else if (redrec->e_rtype == OUTPUT)
		fd = open(redrec->after_expand[0], O_RDWR | O_TRUNC | O_CREAT, 0666);
	else if (redrec->e_rtype == APPEND)
		fd = open(redrec->after_expand[0], O_RDWR | O_CREAT, 0666);
	else if (redrec->e_rtype == HERE_DOC)
		here_doc(redrec, envp, index, &fd);
	return (fd);
}
