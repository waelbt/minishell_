/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:08:26 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/30 05:11:42 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
/*
t_redirec	*ft_close(t_node *head)
{
	t_redirec	*redrec;
	t_redirec	*tmp;

	redrec = NULL;
	while (head != NULL)
	{
		tmp = (t_redirec *) head->content;
		close(tmp->fd);
		head = head->next;
	}
	return (redrec);
}

void	dup_norm(int fildes1, int fildes2)
{
	dup2(fildes1, fildes2);
	close(fildes1);
}

void	*execution(t_node *head, char **env)
{
	int		last_fd;
	int		pipe_fd[2];
	int		id;

	t_redirec	*input;
	t_redirec	*output;
	char		**after_expand;
	t_cmd		*cmd;


	last_fd = -1;
	while (head != NULL)
	{
		pipe(pipe_fd);
		id = fork();
		if (id == 0)
		{
			cmd = (t_cmd *)head->content;
			after_expand = ft_spilt_beta(cmd->args);
			input = get_output_input(cmd->redrec, 1);
			output = get_output_input(cmd->redrec, 0);
			if (head->next != NULL)
				dup_norm(pipe_fd[1], 1);
			if (output != NULL)
				dup_norm(output->fd, 1);
			if (last_fd != -1)
				dup_norm(last_fd, 0);
			if (input != NULL)
				dup_norm(input->fd, 0);
			close(pipe_fd[0]);
			ft_close(cmd->redrec);
			if(execute(after_expand, env))
				exit(0);
			if (after_expand)
				after_expand[0] = check_acces(after_expand[0], env);
			if (after_expand && after_expand[0])
				execve(after_expand[0], after_expand, env);
			exit(0);
		}
		else
		{
			if (head->next != NULL)
				close(pipe_fd[1]);
			if (last_fd != -1)
				close(last_fd);
			ft_close(((t_cmd *)head->content)->redrec);
			last_fd = pipe_fd[0];
		}
		head = head->next;
	}
	while (wait(NULL) > 0)
		;
	return ((void *)1);
}*/
