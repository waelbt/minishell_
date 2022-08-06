/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruin_my_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:48:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/05 16:25:09 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/include/minishell.h"

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

char	*update_pwd(char ***env, int index)
{
	char	*str;
	char	*old_path;

	old_path = NULL;
	if (index != -1)
	{
		str = ft_substr((*env)[index], 4, ft_strlen((*env)[index]));
		old_path = ft_strjoin("OLDPWD=", str);
		free((*env)[index]);
		free(str);
		str = getcwd(NULL, 0);
		(*env)[index] = ft_strjoin("PWD=", str);
		free(str);
		break ;
	}
	return (old_path);
}


void	cd(char *path, char ***env)
{
	int	index;
	char *oldpwd;

	ft_setter(0);
	if (!path)
	{
		printf_error("minishell: ","cd: path is required","\n");
		ft_setter(1);
		return ;
	}
	index = get_index_of_double_char(*env, "PWD");
	if (!(chdir(path) == -1))
	{
		oldpwd = update_pwd(env);
		oldpwd(env, old_path);
	}
	else
	{
		ft_setter(1);
		printf_error("minishell: ", path, ": No such file or directory\n");
	}
}
