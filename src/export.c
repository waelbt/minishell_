/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:13:02 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/03 17:46:55 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char **ft_split_first(char *str, char c)
{
	int		i;
	char	**ret;

	i = 0;
	ret = ft_calloc(3, sizeof(char *));
	while (str[i])
	{
		if (str[i] == c)
		{

			ret[0] = ft_substr(str, 0, ++i);
			ret[1] = ft_substr(str, i, ft_strlen(str));
			ret[3] = NULL;
			return (ret);
		}
		i++;
	}
	return (ret);
}

char **sorted_env(char **env)
{
	int		i;
	int		j;
	int		size;
	char	*temp;	
	
	i = 0;
	j = 0;
	size = 0;
	while (env[size])
			size++;
	size--;
	while (i < size)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if(ft_strcmp(env[j], env[ j + 1]) > 0)
			{
				temp = ft_strdup(env[j]);
				env[j] = ft_strdup(env[j + 1]);
				env[j + 1] = ft_strdup(temp);
			}
			j++;
		}
		i++;
	}
	env[size+1] = NULL;
	return (env);
}

void	print_export(char **envp)
{
	int		i;
	char	**line;
	
	i = 0;
	envp = sorted_env(envp);
	while(envp[i])
	{
		line = ft_split_first(envp[i], '=');
		printf("declare -x %s", line[0]);
		printf("\"%s\"\n", line[1]);
		i++;
		free(line);
	}
}

void	change_existing_value(char ***env, int i, char *var_name, char *var_value)
{

	if (var_value)
	{
		free((*env)[i]);
		(*env)[i] = NULL;
		(*env)[i] = ft_strjoin(var_name, var_value);
	}
}

void	add_value(char ***env, char *var, int i)
{
	char	**envp;

		envp = malloc((i + 1) * sizeof(char *));
		i = -1;
		while ((*env)[++i])
		{
			envp[i] = ft_strdup((*env)[i]);
			(*env)[i] = NULL;
			free((*env)[i]);
		}
		(envp)[i++]= ft_strdup(var);
		(envp)[i] = NULL;
		free(*env);
		*env = malloc(i * sizeof(char *));
		*env = envp;
}


char	*get_value(char	*str, char *var_name)
{
	int		i;
	int		j;
	int		k;
	char	*var_value;

	i = 0;
	j = 0;
	var_value = NULL;
	i = ft_strlen(var_name);
	k = i;
	while(str[k++] != '\0')
		j++;
	var_value = malloc((j + 1) * sizeof(char));
	j = 0;
	while(str[i] != '\0')
		var_value[j++] = str[i++];
	var_value[j] = '\0';
	if (j == 0)
	{
		free (var_value);
		return (NULL);
	}
	return (var_value);
}

char	*get_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;

	while(str[i] && str[i] != '=')
		i++;

	var_name = malloc((i + 1) * sizeof (char));
	i = 0;
	while(str[i] && str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i++] = '=';
	var_name[i] = '\0';
	return (var_name);
}

void	my_export(char ***env, char **vars)
{
	int		i;
	int		j;
	int		key;
	char	*var_name;
	char	*var_value;

	key = 0;
	i = 0;
	j = 1;
	if (vars[1] == NULL)
		print_export(*env);
	else
	{
		while (vars[j])
		{
			var_name = get_name(vars[j]);
			while ((*env)[i])
			{
				if (!(ft_strncmp(var_name, (*env)[i], ft_strlen(var_name))))
				{
					key = 1;
					var_value = get_value(vars[j], var_name);
					if (!var_value)
						break;
					else
						change_existing_value(env, i, var_name, var_value);
					break;
				}
				i++;
			}
			if (!key)
			{
				add_value(env, vars[j], i);
			}
			j++;
			i = 0;
			free(var_value);
			free(var_name);
		}
	}
}
