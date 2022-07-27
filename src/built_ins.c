/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:48:57 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/27 03:16:47 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	ft_check(char *str)
{
	int i;

	if (ft_strncmp(str, "-n", 2))
		return (0);
	i = 2;
	while (str[i])
	{
		if(str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
int		check_flag(char **after_expand, int *check)
{
	int	i;

	i = 1;
	while (after_expand[i])
	{
		if(!ft_check(after_expand[i]))
			return (i);
		*check = 1;
		i++;
	}
	return (-1);
}

void	echo(char **after_expand)
{
	int		i;
	int		check;
	char	*str;

	i = 1;
	check = 0;
	str = NULL;
	ft_setter(0);
	if (!after_expand[1])
		printf("\n");
	else 
	{
		i = check_flag(after_expand, &check);
		if (i == -1)
			return ;
		write(1, after_expand[i], ft_strlen(after_expand[i]));
		while (after_expand[++i])
		{
			write(1, " ", 1);
			write(1, after_expand[i], ft_strlen(after_expand[i]));
		}
		if (check == 0)
			printf("\n");
	}
}

char	**add_to_env(char *str, char **env)
{
	char	**ptr;
	int		index;

	index = 0;
	ptr = (char **) malloc((double_pointer_len(env) + 2) * sizeof(char *));
	while(env[index])
	{
		ptr[index] = ft_strdup(env[index]);
		index++;
	}
	ptr[index++] = str;
	ptr[index] = NULL;
	free_double_char(env, 0);
	return (ptr);
}

void	OLDPWD(char ***env, char *old_path)
{
	int		i;
	int		index;
	char	*str;

	i = 0;
	str = NULL;
	index = get_index_of_double_char(*env, "OLDPWD");
	if(index == -1)
		*env = add_to_env(old_path, *env);
	else
	{
		while ((*env)[i])
		{
			if (i == index)
			{
				free((*env)[i]);
				(*env)[i] = old_path;
				break;
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
	while((*env)[i])
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
			break;
		}
		i++;
	}
	OLDPWD(env, strdup(old_path));
	free(old_path);
}

void	cd(char *path, char ***env)
{
	ft_setter(0);
	if(!path)
		return ;
	if (!(chdir(path) == -1))
		update_paths(env);
	else
	{
		ft_setter(1);
		printf_error("minishell: ", path , ": No such file or directory\n");
	}
}

char	*getpwd(char **env)
{
	int		i;
	char	*str;
	char	**tmp;

	i = 0;
	str = NULL;
	while(env[i])
	{
		tmp = ft_split(env[i], '=');
		free(tmp[1]);
		tmp[1] = ft_substr(env[i], ft_strlen(*tmp) + 1, ft_strlen(env[i]));
		if (!ft_strcmp(tmp[0], "PWD"))
		{
			str = ft_strdup(tmp[1]);
			free_double_char(tmp, 0);
		}
		i++;
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
		printf_error("failed to get the current working directory\n", NULL, NULL);
	}
	else if (!str)
		printf("%s\n", ptr);
	else
		printf("%s\n", str);
}

void	print_env(char **envp)
{
	int	i;
	
	i = 0;
	ft_setter(0);
	while(envp[i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
}
