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
	if (!(ft_strcmp(after_expand[0], check_acces("echo", env))))
			echo(after_expand);
	if (!(ft_strcmp(after_expand[0], check_acces("echo", env))))
	if (!(ft_strcmp(after_expand[0], check_acces("echo", env))))
	if (!(ft_strcmp(after_expand[0], check_acces("echo", env))))
	if (!(ft_strcmp(after_expand[0], check_acces("echo", env))))
	else
		execve(after_expand[0], after_expand, env);
}
