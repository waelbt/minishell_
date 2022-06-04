/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:50:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/04 20:33:28 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINSHELL_H
# define MINSHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "lexer.h"
# include "token.h"
 #include <signal.h>


// typedef struct cmd
// {
// 	int id;
// 	token_T *token;
// 	struct cmd *next;
// 	struct cmd *previous;
// } cmd_T;

// int ReadLine(char *,int ,FILE *);
int		ft_strlen(char *str);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_realloc(void *ptr, size_t size);
char	*ft_strcat(char *dest, char *src);
void	ft_lstadd_front(t_token **list, t_token *new);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstclear(t_token **lst, void (del)(void*));
t_token	*ft_lstlast(t_token *lst);
int		ft_lstsize(t_token *lst);
char	*ft_strchr(char *s, int c);
int		count_element(char *str, char c, int len);
int		ft_strcmp(char *s1, char *s2);
int		get_first(t_lexer lexer);
char	*ft_strjoin(char *s1, char *s2);
int closed_qoutes(t_lexer *lexer, char c, int *bool);
#endif