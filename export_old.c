
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
		if(line[1])
		{
			free(line[1]);
			line[1] = ft_substr(envp[i], ft_strlen(line[0]) + 1, ft_strlen(envp[i]));
		}
		printf("declare -x %s=", line[0]);
		if(!line[1])
			printf("\"\"\n");
		else if(line[1] && strcmp(line[1], "''"))
			printf("\"%s\"\n", line[1]);
		free_double_char(line, 0);
		i++;
	}
	free_double_char(envp, 0);
}

int get_name_index(char *s)
{
	int index;

	index = 1;
	while(s[index] && s[index]!= '+' && s[index] != '=')	
		index++;
	return (index);
}

int	get_key(char *s, int index)
{
	int key;

	if (!s[index])
		key = 0;
	if (s[index] == '=')
		key = 1;
	if (s[index] == '+')
		key = 2;
	return (key);
}
void get_data(char *new_var, t_env_var **var)
{
	int	index;

	index = get_name_index(new_var);
	(*var)->name = ft_substr(new_var, 0, index);
	(*var)->key = get_key(new_var, index);
	if(index + (*var)->key != ft_strlen(new_var))
		(*var)->value = ft_substr(new_var, index + (*var)->key, ft_strlen(new_var));
}
void	edit_exsited_variable(char ***env, t_env_var *var, int index)
{
	char	*last_value;
	char	*tmp;
	if(var->key == 2)
	{
		tmp = var->value;
		if(!((*env)[index]))
			var->value = ft_strjoin("", var->value);
		else
			var->value = ft_strjoin(ft_strchr((*env)[index], '=') + 1, var->value);
		free(tmp);
	}
	free((*env)[index]);
	(*env)[index] = ft_strdup(var->name);
	if(var->value)
	{
		tmp = (*env)[index];
		(*env)[index] = ft_strjoin((*env)[index], "=");
		free(tmp);
		tmp = (*env)[index];
		(*env)[index] = ft_strjoin((*env)[index], var->value);
		free(tmp);
	}
}

void	add_var(char	***env, t_env_var *var, int index)
{
	char	**new_env;
	int		len;
	int		i;
	int		size;


	len = double_pointer_len(*env);
	size = (((index == -1) * (len + 1)) + ((index != -1) * len));
	if(index == -1)
		index = len;
	new_env = (char **) malloc((size + 1) * sizeof(char *));
	i = -1;
	while(++i < len)
		new_env[i] = ft_strdup((*env)[i]);
	i--;
	while(++i <= size)
		new_env[i] = NULL;
	edit_exsited_variable(&new_env , var, index);
	free_double_char(*env, 0);
	*env = new_env;
}


static void ft_free(t_env_var *var)
{
	free(var->name);
	free(var->value);
	free(var);
}
void	my_export(char ***env, char **new_var)
{
	int		j;
	t_env_var	*var;
	int		index;

	j = 0;
	ft_setter(0);
	if (new_var[1] == NULL)
		print_export(*env);
	else
	{
		while (new_var[++j])
		{
			var = (t_env_var *) malloc(sizeof(t_env_var ));
			var->value = NULL;
			get_data(new_var[j], &var);
			index = get_index_of_double_char(*env, var->name);
			if(!ft_check_var_validition(var->name))
			{
				ft_setter(1);
				printf_error("minishell : export: `': not a valid identifier\n", NULL, NULL);
			}
			else if(index == -1 || var->key != 0)
				add_var(env, var, index);
			ft_free(var);
		}
	}
}
