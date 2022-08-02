/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:04:40 by lchokri           #+#    #+#             */
/*   Updated: 2022/08/01 16:45:27 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_var_validition(char *s)
{
	int	index;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	index = 1;
	while (s[index])
	{
		if (!ft_isalnum(s[index]) && s[index] != '_')
			return (0);
		index++;
	}
	return (1);
}

void	delete_var(char ***envp, int index)
{
	int		i[3];
	char	**new_env;

	init_array(i, 3);
	i[2] = double_pointer_len(*envp);
	if (index == -1)
		return ;
	if (i[2] == 0)
	{
		new_env = (char **)malloc(1 * sizeof(char *));
		new_env[0] = NULL;
	}
	else
	{
		new_env = (char **)malloc(i[2] * sizeof(char *));
		while ((*envp)[i[0]])
		{
			if (index != i[0])
				new_env[i[1]++] = ft_strdup((*envp)[i[0]]);
			i[0]++;
		}
		new_env[i[1]] = NULL;
	}
	free_double_char(*envp, 0);
	*envp = new_env;
}

void	unset(char ***envp, char **var)
{
	int	d;
	int	index;

	d = 0;
	ft_setter(0);
	while (var[++d])
	{
		if (!ft_check_var_validition(var[d]))
		{
			ft_setter(1);
			printf_error("minishell: unset: `",
				var[d], "': not a valid identifier\n");
			continue ;
		}
		index = get_index_of_double_char(*envp, var[d]);
		delete_var(envp, index);
	}
}
