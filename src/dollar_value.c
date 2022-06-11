/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <lchokri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:01 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/11 17:36:22 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		find_char(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*dollar_value(char **envp, char *var)
{
	if (!(find_char(var, '=')) && *var)
	{
		while (*envp)
		{
			if(!strncmp(*envp, var, ft_strlen(var)))
				return (ft_strdup(*envp+ft_strlen(var)+1));
			envp++;
		}
	}
	return (ft_strdup(""));
}
