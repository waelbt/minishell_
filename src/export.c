/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:13:02 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/22 22:56:36 by waboutzo         ###   ########.fr       */
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
	int		i[2];
	int		j;
	char	*temp;
	
	i[0] = 0;
	i[1] = 0;
	while (env[i[0]])
	{
		i[1] = 0;
		while (env[i[1] + i[0]])
		{
			if(ft_strcmp(env[i[0]], env[i[1] + i[0]]) > 0)
			{
				temp = ft_strdup(env[i[0]]);
				env[i[0]] = ft_strdup(env[i[1] + i[0]]);
				env[i[1] + i[0]] = ft_strdup(temp);
			}
			i[1]++;
		}
		i[0]++;
	}
	env[i[0]] = NULL;
	return (env);
}

void	print_export(char **env)
{
	int		i;
	char	**line;
	char	**envp;
	
	i = 0;
	envp = sorted_env(ft_strdup_double(env));
	while(envp[i])
	{
		line = ft_split(envp[i], '=');
		free(line[1]);
		line[1] = ft_substr(envp[i], ft_strlen(line[0]) + 1, ft_strlen(envp[i]));
		printf("declare -x %s=", line[0]);
		if(strcmp(line[1], "''"))
			printf("\"%s\"\n", line[1]);
		free_double_char(line, 0);
		i++;
	}
	free_double_char(envp, 0);
}

void	change_existing_value(char ***env, int i, char *var_name, char *var_value)
{
	char	*p;

	p = NULL;
	if (var_name[ft_strlen(var_name) - 1] == '+' && var_value)
		{
			p = (*env)[i];
			(*env)[i] = ft_strjoin((*env)[i], var_value);
			free(p);
		}
	else
	{
		if (var_value)
		{
			free((*env)[i]);
			(*env)[i] = NULL;
			(*env)[i] = ft_strjoin(var_name, var_value);
		}
	}
}

void	check_for_plus(char *var_name)
{
	int		i;

	i = 0;
	while (var_name[i++])
	{
		if (var_name[i] == '+')
			var_name[i] = '\0';
	}
}

void	add_value(char ***env, int i, char *var_name, char *var_value)
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
		check_for_plus(var_name);
		(envp)[i++]= ft_strjoin(var_name, var_value);
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
		if (var_name[i - 1] == '+')
		{
				var_name[i - 1] = '=';
				var_name[i++] = '+';
		}
		else
				var_name[i++] = '=';
		var_name[i] = '\0';
		return (var_name);
}

/*int	plus_equal(char ***env, char *vars)
  {
  int		i;

  i = 0;
  while (vars[i])
  {
  if (vars[i] == '=')
  {
  if (vars[i - 1] == '+')
  {
//concat_var();	
return (1);
}
else
break;
}
i++;
}
return 0;
}
*/
int var_len(char *str)
{
		int	i;

		i = 0;
		while (str[i] && str[i] != '+')
				i++;
		return (i);
}

void	equal(char ***env, char *vars)
{
		int		i;
		int		key;
		char	*var_name;
		char	*var_value;

		key = 0;
		i = 0;
		var_name = get_name(vars);
		printf("var nm = %s len is %d\n", var_name, var_len(var_name));
		while ((*env)[i])
		{
				if (!(ft_strncmp(var_name, (*env)[i], var_len(var_name))))
				{
						printf("well compared name %s in env %s len :%d\n", var_name, (*env)[i], var_len(var_name));
						key = 1;
						var_value = get_value(vars, var_name);
						printf("var val = %s\n", var_value);
						if (!var_value)
								break;
						else
						{
								change_existing_value(env, i, var_name, var_value);
								free(var_value);
						}
						break;
				}
				i++;
		}
		if (!key)
				add_value(env, i, var_name, get_value(vars, var_name));
	i = 0;
	free(var_name);
}

void	my_export(char ***env, char **vars)
{
	int		j;

	j = 1;
	if (vars[1] == NULL)
		print_export(*env);
	else
	{
		while (vars[j])
		{
			if (vars[j][0] == '\0')
				write(2, "minishell : export: `': not a valid identifier\n", 49);
			else
				equal(env, vars[j]);
			j++;
		}
	}
}
