/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:48:57 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/02 02:05:02 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		check_flag(char **after_expand, int *check)
{
	int	i;
	int	j;

	i = 1;
	while (after_expand[i])
	{
		j = 2;
		if (!ft_strncmp(after_expand[i], "-n", 2))
		{
			while (after_expand[i][j] == 'n' && after_expand[i])
				j++;
			if (j == ft_strlen(after_expand[i]))
			{
				*check = 1;
				i++;
			}
			else
				break;
		}
		else
			break;
	}
	return (i);
}

void		echo(char **after_expand)
{
	int		i;
	int		check;
	char	*str;

	i = 1;
	check = 0;
	str = NULL;
	if (!after_expand[1])
		printf("\n");
	else 
	{
		i = check_flag(after_expand, &check);
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

void	OLDPWD(char **env, char *old_path)
{
	int		i;
	int		found;
	char	*str;

	found = 0;
	i = 0;
	str = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			found = 1;
			free(env[i]);
			env[i] = NULL;
			env[i] = ft_strdup(old_path);
			break;
		}
		i++;
	}
	if (!found)
	{
		
	}
}

void	update_paths(char **env)
{
	int		i;
	char	*str;
	char	*old_path;

	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			str = ft_substr(env[i], 4, ft_strlen(env[i]));
			old_path = ft_strjoin("OLDPWD=", str);
			free(env[i]);
			env[i] = NULL;
			free(str);
			str = (getcwd(NULL, 0));
			env[i] = ft_strjoin("PWD=", str);
			free(str);
			break;
		}
		i++;
	}
	OLDPWD(env, old_path);
	free(old_path);
}

void	cd(char *path, char **env)
{
	if (!(chdir(path) == -1))
		update_paths(env);
	else
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);
	}
}

void	pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}

void	print_env(char **envp)
{
	int	i;
	
	i = 0;
	while(envp[i])
	{
		if (find_char(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
}
