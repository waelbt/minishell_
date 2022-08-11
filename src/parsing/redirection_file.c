/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:23:51 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 20:50:07 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*cases(t_lexer *lexer, char **envp)
{
	char	*tmp;

	if (lexer->c == '$' && ft_isalnum(lexer->contents[lexer->i + 1]))
		return (handle_env_var(lexer, envp));
	else
	{
		tmp = lexer_get_current_char_as_string(lexer);
		lexer_advance(lexer);
		return (tmp);
	}
}

char	*here_doc_expand(char *str, char **envp)
{
	t_lexer	*lexer;
	char	*value;
	char	*s;
	char	*tmp;

	lexer = init_lexer(str);
	value = (char *) ft_calloc(1, sizeof(char));
	value[0] = '\0';
	while (lexer->c != '\0')
	{
		s = cases(lexer, envp);
		tmp = value;
		value = ft_strjoin(value, s);
		free(tmp);
		free(s);
	}
	free(str);
	free(lexer);
	return (value);
}

void	here_doc(t_redirec *redirc, char **envp)
{
	int			fd;
	char		*str;

	signal(SIGINT, SIG_DFL);
	fd = open(redirc->path, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
	{
		perror("minishell");
		return ;
	}
	str = readline("> ");
	while (str && ft_strcmp(str, redirc->after_expand[0]))
	{
		if (!ft_strchr(redirc->file, '\'')
			&& !ft_strchr(redirc->file, '"'))
			str = here_doc_expand(str, envp);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	free(str);
	close(fd);
}
