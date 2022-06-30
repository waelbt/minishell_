/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:48:57 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/29 19:39:27 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void		echo(char **after_expand)
{
	int		i;
	int		check;
	char	*str;

	i = 1;
	check = 0;
	str = NULL;
	if (!ft_strncmp(after_expand[1], "-n", 3))
	{
		check = 1;
		i = 2;
	}
	str = ft_strjoin(after_expand[i], " ");
	while(after_expand[++i])
	{
		str = ft_strjoin(str, after_expand[i]);
		if (after_expand[i + 1])
			str = ft_strjoin(str, " ");
	}
	printf("%s", str);
	free (str);
	if (check == 0)
		printf("\n");
}

void	cd(char *path)
{
	printf("%s\n", path);
	if (chdir(path) == -1)
		perror("Error");
}

void	pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}

void	print_env(char **envp)
{
	int	i;
	
	i = 0;
	while(envp[i])
	{
		if (find_char(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
}
