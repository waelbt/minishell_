/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <lchokri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 01:25:25 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/01 17:28:01 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		execute(char **after_expand, char **env)
{
	if (!after_expand)
		return (0);
	if (!(ft_strcmp(after_expand[0], "echo")))
		echo(after_expand);
	else if (!(ft_strcmp(after_expand[0], "cd")))
		cd(after_expand[1], env);
	else if (!(ft_strcmp(after_expand[0], "pwd")))
		pwd();
	else if (!(ft_strcmp(after_expand[0], "export")))
		my_export(&env, after_expand[1]);
	else if (!(ft_strcmp(after_expand[0], "unset")))
		unset(&env, after_expand[1]);
	else if (!(ft_strcmp(after_expand[0], "env")))
		print_env(env);
	else if (!(ft_strcmp(after_expand[0], "exit")))
		my_exit(after_expand[1]);
	else 
	{
		return (0);	
	}
	return (1);
}
