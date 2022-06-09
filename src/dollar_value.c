/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <lchokri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:01 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/09 15:53:19 by lchokri          ###   ########.fr       */
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

void	dollar_value(char **envp, char *var)
{
	if (!(find_char(var, '=')))
	{
		while (*envp)
		{
			if(!strncmp(*envp, var, ft_strlen(var)))
				printf("%s\n", *envp+ft_strlen(var)+1);
			envp++;
		}
	}
}
