/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:01:52 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/02 18:49:18 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	here_doc(t_redirec *redirc, char **envp)
{
	int			fd;
	char		*str;

	signal(SIGINT, SIG_DFL);
	fd = open(redirc->path, O_RDWR | O_TRUNC | O_CREAT, 0666);
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
	free(str);
	close(fd);
}
