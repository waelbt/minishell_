/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:27:46 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/22 21:47:21 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	**my_envp(char **envp)
{
	char	**my_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	my_envp = (char **)malloc(i * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		my_envp[i] = strdup(envp[i]);
		i++;
	}
	return (my_envp);
}
