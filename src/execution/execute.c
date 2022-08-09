/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 01:25:25 by lchokri           #+#    #+#             */
/*   Updated: 2022/08/07 17:34:27 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute(char **after_expand, char ***env, int flag)
{
	if (!(ft_strcmp(after_expand[0], "echo")))
		echo(after_expand);
	else if (!(ft_strcmp(after_expand[0], "cd")))
		cd(after_expand[1], env);
	else if (!(ft_strcmp(after_expand[0], "pwd")))
		pwd(*env);
	else if (!(ft_strcmp(after_expand[0], "export")))
		my_export(env, after_expand);
	else if (!(ft_strcmp(after_expand[0], "unset")))
		unset(env, after_expand);
	else if (!(ft_strcmp(after_expand[0], "env")))
		print_env(*env, after_expand);
	else if (!(ft_strcmp(after_expand[0], "exit")))
		my_exit(after_expand, flag);
	else
		return (0);
	return (1);
}
