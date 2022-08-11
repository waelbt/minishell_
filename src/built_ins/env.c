/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:27:46 by lchokri           #+#    #+#             */
/*   Updated: 2022/08/11 01:36:30 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**my_envp(char **envp)
{
	char	**my_envp;
	int		i;

	i = 0;
	my_envp = (char **)malloc((double_pointer_len(envp) + 1)* sizeof(char *));
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD", 6))
			my_envp[i] = ft_strdup("OLDPWD");
		else
			my_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	my_envp[i] = NULL;
	return (my_envp);
}

void	print_env(char **envp, char **after_expand)
{
	int	i;

	i = 0;
	(void) after_expand;
	if (double_pointer_len(after_expand) != 1)
	{
		printf_error("minishell: ", "env: too many ", "arguments\n");
		ft_setter(1);
		return ;
	}
	ft_setter(0);
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
}
