/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:27:46 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/30 01:00:14 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	**my_envp(char **envp)
{
	char	**my_envp;
	int		i;

	i = 0;
	if(envp)
	{
		while (envp[i])
			i++;
		my_envp = (char **)malloc((i  + 1)* sizeof(char *));
		i = 0;
		while (envp[i])
		{
			my_envp[i] = ft_strdup(envp[i]);
			i++;
		}
		my_envp[i] = NULL;
	}
	return (my_envp);
}
