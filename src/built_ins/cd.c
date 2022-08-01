/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:57:29 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/01 14:27:54 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**add_to_env(char *str, char **env)
{
	char	**ptr;
	int		index;

	index = 0;
	ptr = (char **) malloc((double_pointer_len(env) + 2) * sizeof(char *));
	while (env[index])
	{
		ptr[index] = ft_strdup(env[index]);
		index++;
	}
	ptr[index++] = str;
	ptr[index] = NULL;
	free_double_char(env, 0);
	return (ptr);
}

void	oldpwd(char ***env, char *old_path)
{
	int		i;
	int		index;
	char	*str;

	i = 0;
	str = NULL;
	index = get_index_of_double_char(*env, "OLDPWD");
	if (index == -1)
		*env = add_to_env(old_path, *env);
	else
	{
		while ((*env)[i])
		{
			if (i == index)
			{
				free((*env)[i]);
				(*env)[i] = old_path;
				break ;
			}
		i++;
		}
	}		
}

void	update_paths(char ***env)
{
	int		i;
	char	*str;
	char	*old_path;

	i = 0;
	old_path = NULL;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], "PWD=", 4))
		{
			str = ft_substr((*env)[i], 4, ft_strlen((*env)[i]));
			old_path = ft_strjoin("OLDPWD=", str);
			free((*env)[i]);
			free(str);
			str = getcwd(NULL, 0);
			(*env)[i] = ft_strjoin("PWD=", str);
			free(str);
			break ;
		}
		i++;
	}
	oldpwd(env, strdup(old_path));
	free(old_path);
}

void	cd(char *path, char ***env)
{
	ft_setter(0);
	if (!path)
		return ;
	if (!(chdir(path) == -1))
		update_paths(env);
	else
	{
		ft_setter(1);
		printf_error("minishell: ", path, ": No such file or directory\n");
	}
}
