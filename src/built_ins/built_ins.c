/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:48:57 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/22 21:32:47 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (chdir(path) < 0)
		perror("Error");
}

void	pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}
