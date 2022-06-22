/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:48:57 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/21 20:11:05 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

int main(int ac, char **av)
{
	(void)ac;
	echo(av);
}
