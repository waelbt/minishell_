/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:13:02 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/25 15:33:22 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		get_j(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
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
	while (i < size)
	{
		j = 0;
		while (j < size -1 - i)
		{
			if(ft_strcmp(env[j], env[j+1]) > 0)
			{
				temp = ft_strdup(env[j]);
				env[j] = ft_strdup(env[j + 1]);
				env[j + 1] = ft_strdup(temp);
			}
			j++;
		}
		i++;
	}
	return (env);
}

void	print_export(char **envp)
{
	int	i;
	
	i = 0;
	envp = sorted_env(envp);
	while(envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

void	right_value(char **str)
{
	char	*s;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	int		j;

	j = 0;
	if ((s = ft_strchr(*str, '=')))
		{
			tmp = ft_strjoin("\"", ++s);
	//		tmp2 = *str;
			tmp1 = tmp;
			tmp = ft_strjoin(tmp, "\"");
			j = get_j(*str);
			*str = ft_substr(*str, 0, j + 1);
			tmp2 = *str;
			*str = ft_strjoin(*str, tmp);
			free(tmp2);
			free(tmp1);
		}
	else
	{
		tmp = ft_strdup("");
		*str = ft_strjoin(*str, tmp);
		free(tmp);
	}
}
	
void	my_export(char ***envp, char *value)
{
	int		i;
	char	**new_envp;

	i = 0;
	if (value == NULL)
		print_export(*envp);
	else
	{
		right_value(&value);
		while ((*envp)[i])
			i++;
		new_envp = (char **)malloc((i + 2) * sizeof(char *));
		i = 0;
		while ((*envp)[i])
		{
			new_envp[i] = ft_strdup((*envp)[i]);
			i++;
		}
		new_envp[i] = ft_strdup(value);
		i++;
		new_envp[i] = NULL;
		*envp = new_envp;
		*envp = sorted_env(*envp);
		free(value);
	}
}
/*ba9in leaks mcha3ch3in o function d c99 as strdup*/
/*int main(int ac, char **av)
{
	int		i;
	char	**str;

	i = 0;
	my_export(&av, "some=");
	while(av[i])
	{
		printf("```%s```\n", av[i]);
		i++;
	}
	//system("leaks a.out");
}
*/
