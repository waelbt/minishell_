/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:30:12 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/18 20:14:15 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	**p;
	char	*path;

	p = paths;
	path = NULL;
	while (envp)
	{
		if ((ft_strncmp("PATH", *envp, 4)) == 0)
			break;
		envp++;
	}
	paths = ft_split(*envp+5, ':');
	while (*paths)
	{
		*paths = ft_strjoin(*paths, cmd);
		if (access(*paths, X_OK) == 0)
			path = ft_strdup(*paths);
		free (*paths);
		paths++;
	}
//	free(p); where da fuck is that dbl free?
	return (path);
}

void	not_accessible(char **av, char **cmd1, char **cmd2, char **envp)
{
	char	**argv1;
	char	**argv2;

	argv1 = ft_split(av[2], ' ' );
	argv2 = ft_split(av[3], ' ' );
	if (access(argv1[0], X_OK))
	{
		*cmd1 = ft_strjoin("/", argv1[0]);
		*cmd1 = check_cmd(*cmd1, envp);
	}
	else
		*cmd1 = av[2];
	if (access(argv2[0], X_OK))
	{
		*cmd2 = ft_strjoin("/", argv2[0]);
		*cmd2 = check_cmd(*cmd2, envp);
	}
	else
		*cmd2 = av[3];
}

void	manage_err()
{
	perror("Error");
	exit(EXIT_FAILURE);
}
//pipe writes to fd[1]
int main(int ac, char **av, char **envp)
{
	int		fd[2];
	int		end[2];
	int		chld_pid;
	char	*cmd1;
	char	*cmd2;
	char	**argv1;
	char	**argv2;

	if (ac == 5)
	{
		argv1 = ft_split(av[2], ' ' );
		argv2 = ft_split(av[3], ' ' );
		if ((fd[0] = open(av[1], O_RDONLY))== -1)
			manage_err();
		if ((fd[1] = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0666))== -1)
			manage_err();
		not_accessible(av, &argv1[0], &argv2[0], envp);
		pipe(end);
		chld_pid = fork();
		if (chld_pid == 0)
		{
			close(end[0]);
			dup2(fd[0], 0);
			dup2(end[1], 1);
			execve(argv1[0], argv1, envp);
		}
		else
		{
			wait(NULL);
			close(end[1]);
		}
		chld_pid = fork();
		if (chld_pid == 0)
		{
			close(end[1]);
			dup2(end[0], 0);
			dup2(fd[1], 1);
			execve(argv2[0], argv2, envp);
			printf("we're in child 2\n");
		}
		else
		{
			wait(NULL);
			printf("we're back to parent 2\n");
		}
	}
	else
		write(2, "Error!\nUsage: ./pipex f1 cmd1 cmd2 f2\n", 41);
}
