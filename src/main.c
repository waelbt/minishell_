/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:48:37 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/21 17:32:10 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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

t_node	*handler(t_lexer *lexer)
{
	t_token	*token[2];
	t_node	*node[2];

	node[1] = NULL;
	token[0] = lexer_get_next_token(lexer);
	if (!ft_strcmp(token[0]->value, "|"))
	{
		ft_setter(258);
		printf_error(NULL, "parse error near `|'\n", NULL);
		return (ft_free(token[0], lexer, NULL, node[1]));
	}
	while (token[0]->e_type != TOKEN_EOF)
	{
		if (token[0]->e_type == TOKEN_ERROR)
			return (ft_free(token[0], lexer, NULL, node[1]));
		node[0] = ft_lstnew((void *) init_cmd(lexer, &token[0]));
		if (!node[0])
			return (ft_free(token[0], lexer, NULL, node[1]));
		ft_lstadd_back(&node[1], node[0]);
		token[1] = token[0];
		token[0] = lexer_get_next_token(lexer);
		if (!ft_pipe_check(token[0], token[1]))
			return (ft_free(token[0], lexer, NULL, node[1]));
	}
	return (ft_free(token[0], lexer, node[1], NULL));
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
	ft_setter(1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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
		env =  my_envp(envp);
		while (1)
		{
			signal(SIGINT, sig_handler);
			signal(SIGQUIT, SIG_IGN);
			str = readline("\033[0;35mminishell$ \033[0;37m");
			if(!str)
				break;
			add_history (str);
			cmd = handler(init_lexer(str));
			if (parsing(&cmd, env, &index))
				execution(cmd, &env);
			ft_unlik(&index);
			free_node(&cmd);
			free(str);
		}
		free(str);
		write(1, "exit\n", 5);
		free(env);
	}
	return (0);
}
