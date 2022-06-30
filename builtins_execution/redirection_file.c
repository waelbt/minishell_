/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:01:52 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/30 08:50:18 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
extern struct vars vr;

void	here_doc(t_redirec *redirc, char **envp, int *index, int *fd)
{
	char		*str[4];

	str[1] = ft_itoa(*index);
	str[2] = ft_strjoin("/var/TMP/her_doc", str[1]);
	str[3] = NULL;
	*fd = open(str[2], O_RDWR | O_CREAT, 0666);
	if (*fd < 0)
		return ;
	vr.h_doc = 1;
	vr.fd_cp = *fd;
	(*index)++;
	write(1, ">", 1);
	str[0] = readline("\033[0;35> \033[0;37m");
	while (ft_strcmp(str[0], redirc->file))
	{
		if (!ft_strchr(redirc->previous_delimiter, '\'')
			&& !ft_strchr(redirc->previous_delimiter, '"'))
			str[0] = pure_arg(str[0], envp);
		write(*fd, str[0], ft_strlen(str[0]));
		write(*fd, "\n", 1);
		free(str[0]);
		write(1, ">", 1);
		str[0] = readline("\033[0;35> \033[0;37m");
	}
	vr.h_doc = 0;
	close(*fd);
	*fd = open(str[2], O_RDWR | O_CREAT, 0666);
	free_double_char(str, 1);
}

int	open_file_descriptor(t_redirec	*redrec, char **envp, int *index)
{
	int	fd;

	if (redrec->e_rtype == INPUT)
		fd = open(redrec->file, O_RDWR, 0666);
	else if (redrec->e_rtype == OUTPUT)
		fd = open(redrec->file, O_RDWR | O_TRUNC | O_CREAT, 0666);
	else if (redrec->e_rtype == APPEND)
		fd = open(redrec->file, O_RDWR | O_CREAT, 0666);
	else if (redrec->e_rtype == HERE_DOC)
	{
		vr.pid = fork();
		if (vr.pid != 0)
			wait(NULL);
		else
		{
			here_doc(redrec, envp, index, &fd);
			free(redrec->previous_delimiter);
		}
	}
	return (fd);
}
