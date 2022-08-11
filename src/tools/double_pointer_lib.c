/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_pointer_lib.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:09:15 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 18:30:02 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**sorted_env(char **env)
{
	int		i[2];
	char	*temp;

	i[0] = 0;
	i[1] = 0;
	while (env[i[0]])
	{
		i[1] = 0;
		while (env[i[1] + i[0]])
		{
			if (ft_strcmp(env[i[0]], env[i[1] + i[0]]) > 0)
			{
				temp = env[i[0]];
				env[i[0]] = env[i[1] + i[0]];
				env[i[1] + i[0]] = temp;
			}
			i[1]++;
		}
		i[0]++;
	}
	env[i[0]] = NULL;
	return (env);
}

char	**join_double_pointer(char **str, char **ptr)
{
	char	**join;
	int		len[2];
	int		index[2];

	if (!ptr)
		return (str);
	index[0] = 0;
	index[1] = 0;
	len[0] = double_pointer_len(str);
	len[1] = len[0] + double_pointer_len(ptr);
	join = (char **) ft_calloc((len[1] + 1), sizeof(char *));
	if (!join)
		return (NULL);
	while (index[0] < len[1])
	{
		if (index[0] < len[0])
			join[index[0]] = str[index[0]];
		else if (index[0] >= len[0])
			join[index[0]] = ptr[index[1]++];
		index[0]++;
	}
	join[index[0]] = NULL;
	free(str);
	free(ptr);
	return (join);
}

char	**ft_strdup_double(char **ptr)
{
	char	**str;
	int		i;
	int		len;

	len = double_pointer_len(ptr);
	str = (char **)malloc((len + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = ft_strdup(ptr[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**env_split(char **envp, int i)
{
	char	**line;

	line = ft_split(envp[i], '=');
	if (line[1])
	{
		free(line[1]);
		line[1] = ft_substr(envp[i], ft_strlen(line[0]) + 1,
				ft_strlen(envp[i]));
	}
	return (line);
}

int	get_index_of_double_char(char **envp, char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			tmp = ft_split(envp[i], '=');
			if (!ft_strcmp(tmp[0], var))
			{
				free_double_char(tmp, 0);
				return (i);
			}
			free_double_char(tmp, 0);
			i++;
		}
	}
	return (-1);
}
