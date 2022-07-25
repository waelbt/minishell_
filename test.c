/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:57:32 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/23 21:05:01 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/include/minishell.h"

int main(int argc, char **argv, char **env)
{
	char **str;
	int	fd;
	int	copie;
	int id;

	
	if(argc == 2)
	{
		str = ft_split(strdup("cat"), 32);
		fd = open(argv[1], O_RDWR | O_CREAT, 0666);
		copie = dup(1);
		dup2(fd, 1);
		close(1);
		id = fork();
		if(id == 0)
			execve(str[0], str, env);
		else
		{
			wait(NULL);
			dup2(copie, 1);
			close(1);
		}
	}	
}
