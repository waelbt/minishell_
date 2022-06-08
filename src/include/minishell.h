/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:50:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/08 12:10:42 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "lexer.h"
# include "token.h"
# include <signal.h>

typedef struct args
{
	//t_node		*after_expand;
	char	*value;
}	t_args;

typedef struct redirection
{
	int		fd;
	enum
	{
		OUTPUT,
		INPUT,
		R_OUTPUT,
		R_INPUT,
		ERROR,
	}e_rtype;
	char	*file;
}	t_redirec;

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;


typedef struct cmd
{
	t_node		*args;
	t_node		*redrec;
}	t_cmd;


int			ft_strlen(char *str);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		*ft_realloc(void *ptr, size_t size);
char		*ft_strcat(char *dest, char *src);
void		ft_lstadd_front(t_node **list, t_node *new);
void		ft_lstadd_back(t_node **lst, t_node *new);
void		ft_lstclear(t_node **lst, void (del)(void*));
t_node		*ft_lstlast(t_node *lst);
int			ft_lstsize(t_node *lst);
void		ft_lstdelone(t_node *lst, void (*del)(void *));
char		*ft_strchr(char *s, int c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char *s1, char *s2);
int			closed_qoutes(t_lexer *lexer, char c, int *bool);
void		error_handler(char *str);
t_node		*ft_lstnew(void *content);
t_redirec	*init_redirection(char *str, t_lexer *lexer);
t_args  	*init_arg(char *str);
void		printf_args(t_node *head);
void		printf_redrection(t_node *head);
void		printf_node(t_node *head);
char		*ft_strdup(const char *s1);
void		free_node(t_node **head);
t_cmd		*init_cmd(t_lexer *lexer, t_token **token);
#endif