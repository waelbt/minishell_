/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:01:52 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/21 17:48:38 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	here_doc(t_redirec *redirc, char **envp)
{
	static int	index = 0;
	char		*str;
	char		*tmp;
	char		*tmp2;
	int			fd;

	tmp = ft_itoa(index);
	tmp2 = ft_strjoin("/var/TMP/her_doc", tmp);
	fd = open(tmp2 , O_RDWR | O_CREAT, 0777);
	free(tmp2);
	index++;
	free(tmp);
	/*wach 5assni ndir O_TRUNC fe had lcas ?*/
	if (fd < 0)
		return (fd);
	str = readline("\033[0;35> \033[0;37m");
	//  && ft_strncmp(str, "EOF", 3)
	while (ft_strncmp(str, redirc->file, ft_strlen(redirc->file)))
	{
		str = pure_arg(str, envp);
		write(fd, str, ft_strlen(str));
		free(str);
		str = readline("\033[0;35> \033[0;37m");
	}
	free(str);
	return (fd);
}

int	open_file_descriptor(t_redirec	*redrec, char **envp)
{
	int	fd;

	if (redrec->e_rtype == INPUT)
		fd = open(redrec->file, O_RDWR, 0666);
	else if (redrec->e_rtype == OUTPUT)
		fd = open(redrec->file, O_RDWR | O_TRUNC | O_CREAT, 0666);
	else if (redrec->e_rtype == APPEND)
		fd = open(redrec->file, O_RDWR | O_CREAT, 0666);
	else if (redrec->e_rtype == HERE_DOC)
		fd = here_doc(redrec, envp);
	return (fd);
}
