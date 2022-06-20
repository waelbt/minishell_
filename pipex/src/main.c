/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:19:46 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/20 11:49:28 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths = NULL;
	char	*path;
	int i;

	path = NULL;
	while (envp)
	{
		if ((ft_strncmp("PATH", *envp, 4)) == 0)
			break;
		envp++;
	}
	paths = ft_split(*envp+5, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], ft_strdup(cmd));
		if (access(paths[i], X_OK) == 0)
			path = ft_strdup(paths[i]);
		free(paths[i]);
		i++;
	}
	free(paths);
	free(cmd);
	return (path);
}

void ft_free(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int args_checker(int argc, char **argv)
{
	if(!ft_strcmp(argv[1], argv[argc - 1]))
		return (0);
	return (1);
}

char	*check_acces(char *cmd, char **envp)
{
	if (access(cmd, X_OK))
	{
		if(ft_strchr(cmd, '/'))
			return (NULL);
		cmd = ft_strjoin(ft_strdup("/"), cmd);
		cmd = check_cmd(cmd, envp);
	}
	return (cmd);
}

void child_work(int n, int *fd, char **env, char **argv)
{
	int i = 0;
	int last_fd;
	int id;
	int pipe_fd[2];
	char	**cmd;

	last_fd = -1;

	while(i < n)
	{
		cmd = ft_split(argv[2 + i], 32);
		cmd[0] = check_acces(cmd[0], env);
		pipe(pipe_fd);
		id = fork();
		if(id == 0)
		{
			if(i != n - 1)
			{
				dup2(pipe_fd[1], 1);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
			}
			if(i == n - 1)
			{
				dup2(fd[1], 1);
				close(fd[1]);
			}
			if(last_fd != -1)
			{
				dup2(last_fd, 0);
				close(last_fd);
			}
			if(i == 0)
			{
				dup2(fd[0], 0);
				close(fd[0]);
			}
			execve(cmd[0], cmd, env);
		}
		else
		{
			if(i != n - 1)
			{
				close(pipe_fd[1]);
			}
			if(last_fd != -1)
			{
				close(last_fd);
			}
			last_fd = pipe_fd[0];
			ft_free(cmd);
		}
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	int fd[2];

	if(args_checker(argc,argv))
	{
		fd[0] = open(argv[1], O_RDONLY);
		fd[1] = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
		if(fd[0] < 0 || fd[1] < 0)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		child_work(argc - 3, fd, env, argv);
		//printf("%s %s\n", cmd[0], cmd[1]);
	}
	else
		printf("invalid argements\n");
	return (0);
	//child_work(2, fd);
	//while(1);
}