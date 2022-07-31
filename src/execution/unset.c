/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:04:40 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/30 09:00:30 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_index_of_double_char(char **envp, char *var)
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

int ft_check_var_validition(char *s)
{
	int index;

	if(!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	index = 1;
	while(s[index])
	{
		if(!ft_isalnum(s[index]) && s[index] != '_')
			return (0);
		index++;
	}
	return (1);
}

void unset(char ***envp, char **var)
{
	int		d;
	int 	len;
	int		i;
	int		j;
	int		index;
	char	**new_env;

	d = 0;
	while(var[++d])
	{
		i = 0;
		j = 0;
		len = double_pointer_len(*envp);
		if(!ft_check_var_validition(var[d]))
		{
			ft_setter(1);
			printf_error("minishell: unset: `", var[d], "': not a valid identifier\n");
			continue;
		}
		ft_setter(0);
		index = get_index_of_double_char(*envp, var[d]);
		new_env = NULL;
		if(index != -1)
		{
			if(len == 0)
			{
				new_env = (char **)malloc(1 * sizeof(char *));
				new_env[0] = NULL;
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
			}
			*envp = new_env;
		}
	}
	
}