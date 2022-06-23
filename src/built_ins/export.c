/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:13:02 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/23 22:13:47 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	free_double_char(char **tmp)
{
	int	i;

	i = 0;
	if(!tmp)
		return ;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}
/* strduppp*/
void	print_export(char **envp)
{
	int	i;
	
	i = 0;
	while(envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

void	export(char ***envp, char *value)
{
	int		i;
	char	**new_envp;

	i = 0;
	if (value == NULL)
		print_export(*envp);
	else
	{
		while ((*envp)[i])
			i++;
		new_envp = (char **)malloc((i + 1) * sizeof(char *));
		i = 0;
		while ((*envp)[i])
		{
			new_envp[i] = strdup((*envp)[i]);
			i++;
		}
		new_envp[i++] = strdup(value);
		new_envp[i] = NULL;
		*envp = my_envp(new_envp);
	}
}

int main(int ac, char **av)
{
	int		i;

	i = 0;
	export(&av, "some var");
	while(av[i])
	{
		printf("```%s```\n", av[i]);
		i++;
	}
}

