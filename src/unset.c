/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:04:40 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/21 13:54:06 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	get_unset_index(char **envp, char *var)
{
	int i;
	char **tmp;

	i = 0;
	if(envp)
	{
		while(envp[i])
		{
			tmp = ft_split(envp[i], '=');
			if(!ft_strcmp(tmp[0], var))
			{
				free_double_char(tmp, 0);
				return (i);
			}
			free_double_char(tmp, 0);
			i++;
		}
	}
	return (-1);
}

void unset(char ***envp, char *var)
{
	int 	len;
	int		i;
	int		j;
	int		index;
	char	**new_env;

	i = 0;
	j = 0;
	len = double_pointer_len(*envp);
	index = get_unset_index(*envp, var);
	new_env = NULL;
	if(index != -1)
	{
		if(len == 0)
		{
			new_env = (char **)malloc(1 * sizeof(char *));
			new_env = NULL;
		}
		else
		{
			new_env = (char **)malloc(len * sizeof(char *));
			while((*envp)[i])
			{
				if(index != i)
					new_env[j++] = ft_strdup((*envp)[i]);
				i++;				
			}
			new_env[j] = NULL;
			free_double_char(*envp, 0);
			*envp = new_env;
		}
	}
	
}