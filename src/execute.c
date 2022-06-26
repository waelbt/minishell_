/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 01:25:25 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/26 02:34:33 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	execute(char **after_expand, char **env)
{
	printf("%s\n", after_expand[0]);
	if (!(ft_strcmp(after_expand[0], "echo")))
	{
			printf("thaaaaaat bitch!!");
			//sleep(1);
			echo(after_expand);
	}
	else
	{
			printf("that bitch!!");
			sleep(1);
		execve(after_expand[0], after_expand, env);
	}
}
