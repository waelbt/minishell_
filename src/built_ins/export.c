/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:13:02 by lchokri           #+#    #+#             */
/*   Updated: 2022/08/11 19:05:02 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(char **env)
{
	int		i;
	char	**line;
	char	**envp;

	i = -1;
	envp = sorted_env(ft_strdup_double(env));
	while (envp[++i])
	{
		line = env_split(env, i);
		printf("declare -x %s", line[0]);
		if (!ft_strchr(envp[i], '='))
		{
			printf("\n");
			free_double_char(line, 0);
			continue ;
		}
		printf("=");
		if (!line[1])
			printf("\"\"\n");
		else if (line[1] && strcmp(line[1], "''"))
			printf("\"%s\"\n", line[1]);
		free_double_char(line, 0);
	}
	free_double_char(envp, 0);
}

void	init_var(char *new_var, t_env_var **var, char **env)
{
	t_env_var	*tmp;
	int			index;
	int			value_start;

	tmp = *var;
	index = 0;
	tmp->e_stat = EXISTED;
	while (new_var[index] && new_var[index] != '='
		&& (new_var[index] != '+' || new_var[index + 1] != '='))
		index++;
	tmp->e_type = SET_VALUE;
	tmp->name = ft_substr(new_var, 0, index);
	tmp->index = get_index_of_double_char(env, tmp->name);
	tmp->key = get_key(new_var, index);
	value_start = index + tmp->key;
	tmp->value = ft_substr(new_var, value_start, ft_strlen(new_var));
	if (tmp->index == -1)
		tmp->e_stat = NOT;
	else if (tmp->e_stat == EXISTED && tmp->key == 0)
		tmp->e_type = NOTHING;
	else if (tmp->key == 2)
		tmp->e_type = CONCATENATE;
}

void	edit_exsited_variable(char ***env, t_env_var *var)
{
	char	*ptr[3];

	ptr[1] = (*env)[var->index];
	(*env)[var->index] = ft_strdup(var->name);
	if (var->key != 0)
	{
		ptr[2] = ft_strdup(var->value);
		if (var->e_type == CONCATENATE)
		{
			free(ptr[2]);
			if (!ft_strchr(ptr[1], '='))
				ptr[0] = "";
			else
				ptr[0] = ft_strchr(ptr[1], '=') + 1;
			ptr[2] = ft_strjoin(ptr[0], var->value);
		}
		free(ptr[1]);
		free((*env)[var->index]);
		(*env)[var->index] = ft_strjoin(var->name, "=");
		ptr[1] = (*env)[var->index];
		(*env)[var->index] = ft_strjoin((*env)[var->index], ptr[2]);
		free(ptr[1]);
		free(ptr[2]);
	}
}

void	add_var(char ***env, t_env_var *var)
{
	char	**new_env;
	int		len;
	int		i;
	int		size;

	len = double_pointer_len(*env);
	size = (((var->e_stat == NOT) * (len + 1)) + ((var->e_stat != NOT) * len));
	if (var->e_stat == NOT)
		var->index = len;
	new_env = (char **) malloc((size + 1) * sizeof(char *));
	i = -1;
	while (++i < len)
		new_env[i] = ft_strdup((*env)[i]);
	if (var->e_stat == NOT)
		new_env[i++] = NULL;
	new_env[i++] = NULL;
	edit_exsited_variable(&new_env, var);
	free_double_char(*env, 0);
	*env = new_env;
}

void	my_export(char ***env, char **new_var)
{
	int			j;
	t_env_var	*var;

	j = 0;
	ft_setter(0);
	if (new_var[1] == NULL)
		print_export(*env);
	else
	{
		while (new_var[++j])
		{
			var = (t_env_var *) malloc(sizeof(t_env_var));
			var->value = NULL;
			init_var(new_var[j], &var, *env);
			if (!ft_check_var_validition(var->name))
			{
				ft_setter(1);
				printf_error("minishell : export: `': not a valid identifier\n",
					NULL, NULL);
			}
			else if (var->e_type != NOTHING)
				add_var(env, var);
			free_var(var);
		}
	}
}
