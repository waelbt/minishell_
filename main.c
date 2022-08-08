/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:48:37 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/08 17:01:00 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/include/minishell.h"

void	*ft_free(t_token *token, t_lexer *lexer, t_node *node, t_node *tmp)
{
	if (!node)
		free_node(&tmp);
	free(lexer);
	free(token->value);
	free(token);
	return (node);
}

int	ft_pipe_check(t_token *token, t_token *previous)
{
	int	value;

	value = 0;
	if (ft_strchr(token->value, '|'))
	{
		ft_setter(258);
		printf_error(NULL, "parse error near `||'\n", NULL);
	}
	else if (previous->e_type == TOKEN_PIPE && token->e_type == TOKEN_EOF)
	{
		ft_setter(258);
		printf_error(NULL, "parse error near `|'\n", NULL);
	}
	else
		value = 1;
	free(previous->value);
	free(previous);
	return (value);
}

void	ft_unlik(int *index)
{
	char	*tmp[2];

	while (*index > -1)
	{
		tmp[0] = ft_itoa(*index);
		tmp[1] = ft_strjoin("/var/TMP/her_doc", tmp[0]);
		unlink(tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		(*index)--;
	}
	*index = 0;
}

void	sig_handler(int sig)
{
	(void) sig;
	ft_setter(1);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_node	*cmd;
	int		index;
	char	**env;

	if (argc == 1)
	{
		(void) argv;
		env =  my_envp(envp);
		while (1)
		{
			signal(SIGINT, sig_handler);
			signal(SIGQUIT, SIG_IGN);
			str = readline("minishell$ ");
			if(!str)
				break;
			if (ft_strcmp(str, ""))
				add_history (str);
			cmd = handler(init_lexer(str));
			if(parsing(&cmd, env, &index))
			{
				if (ft_lstsize(cmd) == 1)
					execution_cmd(cmd, &env);
				else
					execution_multi_cmds(cmd, env);
			}
			ft_unlik(&index);
			free_node(&cmd);
			free(str);
		}
		free(cwd_saver);
		write(1, "exit\n", 5);
		free(env);
	}
	return (0);
}
