/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:57:59 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/01 15:36:29 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*getpwd(char **env)
{
	int		i;
	char	*str;
	char	**tmp;

	i = 0;
	str = NULL;
	while (env[i])
	{
		tmp = env_split(env, i);
		if (!ft_strcmp(tmp[0], "PWD"))
			str = ft_strdup(tmp[1]);
		i++;
		free_double_char(tmp, 0);
	}
	return (str);
}

void	pwd(char **env)
{
	char	*str;
	char	*ptr;

	str = getpwd(env);
	ptr = getcwd(NULL, 0);
	ft_setter(0);
	if (!str && !ptr)
	{
		ft_setter(127);
		printf_error("failed to get the current working directory\n",
			NULL, NULL);
	}
	else if (!str)
		printf("%s\n", ptr);
	else
		printf("%s\n", str);
	free(str);
	free(ptr);
}
