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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	**my_envp(char **envp)
{
	char	**my_envp;
	int		i;

	i = 0; 
	while (envp[i])
		i++;
	my_envp = malloc(i * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		my_envp[i] = strdup(envp[i]);
		i++;
	}
	return (my_envp);
}
int main(int ac, char **av, char **envp)
{
	char	**my_av;
	int		i;

	i = 0;
	my_av = my_envp(envp);

	while(my_av[i])
	printf("%s\n", my_av[i++]);
}
