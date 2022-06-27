/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 01:25:25 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/27 01:48:05 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	execute(char **after_expand, char **env)
{
	if (!(ft_strcmp(after_expand[0], check_acces("echo", env))))
		echo(after_expand);
	else if (!(ft_strcmp(after_expand[0], check_acces("cd", env))))
		cd(after_expand[1]);
	else if (!(ft_strcmp(after_expand[0], check_acces("pwd", env))))
		pwd();
	else if (!(ft_strcmp(after_expand[0], "export")))
		my_export(&env, after_expand[1]);
	else if (!(ft_strcmp(after_expand[0], "unset")))
		unset(&env, after_expand[1]);
	else if (!(ft_strcmp(after_expand[0], check_acces("env", env))))
		print_env(env);
	else if (!(ft_strcmp(after_expand[0], "exit")))
		my_exit(after_expand[1]);
	else
		{
		printf("runned by execve\n");
		execve(after_expand[0], after_expand, env);
		}
}
