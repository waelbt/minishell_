/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:04:40 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/25 22:00:18 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset(char ***envp, char *var)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while ((*envp)[j])
		j++;
	while ((*envp)[i])
	{
		tmp = ft_split((*envp)[i], '=');
		if (!ft_strcmp(tmp[0], var))
		{
			while (i < j-1)
			{
				(*envp)[i] = strdup((*envp)[i + 1]);
				i++;
			}
			(*envp)[i] = NULL;
		}
		free_double_char(tmp);
		i++;
	}
}
