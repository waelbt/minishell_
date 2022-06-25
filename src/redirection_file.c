/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:01:52 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/24 16:30:25 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	here_doc(t_redirec *redirc, char **envp, int *index)
{
	char		*str;
	char		*tmp;
	char		*tmp2;
	int			fd;

	tmp = ft_itoa(*index);
	tmp2 = ft_strjoin("/var/TMP/her_doc", tmp);
	fd = open(tmp2 , O_RDWR | O_CREAT, 0666);
	(*index)++;
	free(tmp);
	/*wach 5assni ndir O_TRUNC fe had lcas ?*/
	/*new line*/
	if (fd < 0)
		return (fd);
	str = readline("\033[0;35> \033[0;37m");
	//  && ft_strncmp(str, "EOF", 3)
	while (ft_strcmp(str, redirc->file))
	{
		str = pure_arg(str, envp);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("\033[0;35> \033[0;37m");
	}
	close(fd);
	fd = open(tmp2 , O_RDWR | O_CREAT, 0666);
	free(tmp2);
	free(str);
	return (fd);
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
		fd = here_doc(redrec, envp, index);
	return (fd);
}
