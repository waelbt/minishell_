/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:57:29 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/07 19:02:24 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char *cwd_saver;

void	update_pwd(char ***env)
{
	int		index;
	char	*str;

	index = get_index_of_double_char(*env, "PWD");
	if (index != -1)
	{
		free((*env)[index]);
		str = getcwd(NULL, 0);
		(*env)[index] = ft_strjoin("PWD=", str);
		free(str);
	}
}

void	update_oldpwd(char ***env, char *get_cwd,char *cwd_env)
{
	int		index;
	char	*str;
	char	*tmp;

	str = NULL;
	if (cwd_env)
		str = cwd_env;
	else if (get_cwd)
		str = get_cwd;
	index = get_index_of_double_char(*env, "OLDPWD");
	if (index != -1)
	{
		free((*env)[index]);
		(*env)[index] = ft_strdup("OLDPWD");
		if(str && !access(cwd_saver, X_OK))
		{
			tmp = (*env)[index];
			(*env)[index] = ft_strjoin((*env)[index], "=");
			free(tmp);
			tmp = (*env)[index];
			(*env)[index] = ft_strjoin((*env)[index], str);
			free(tmp);
		}
	}
}

void	cd(char *path, char ***env)
{
	char	*cwd_env;
	char	*get_cwd;

	
	ft_setter(0);
	if (!path)
	{
		printf_error("minishell: ","cd: path is required","\n");
		ft_setter(1);
		return ;
	}
	get_cwd = getcwd(NULL, 0);
	cwd_env = getpwd(*env);
	if (!(chdir(path) == -1))
	{
		update_pwd(env);
		update_oldpwd(env, get_cwd,cwd_env);
	}
	else
	{
		ft_setter(1);
		printf_error("minishell: ", path, ": No such file or directory\n");
	}
	free (cwd_env);
	free (get_cwd);
}
