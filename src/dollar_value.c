/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:01 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/09 15:01:54 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	dollar_value(char **envp, char *var)
{
	while (*envp)
	{
		if(!strncmp(*envp, var, ft_strlen(var)))
			printf("%s\n", *envp+ft_strlen(var)+1);
		envp++;
	}
}
int main(int ac, char **av, char **envp)
{
	dollar_value(envp, av[1]);
}
