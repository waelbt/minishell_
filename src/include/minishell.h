/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:50:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/05/28 18:14:39 by waboutzo         ###   ########.fr       */
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
void	ft_lstadd_front(token_T **list, token_T *new);
void	ft_lstadd_back(token_T **lst, token_T *new);
void	ft_lstclear(token_T **lst, void (del)(void*));
token_T	*ft_lstlast(token_T *lst);
int		ft_lstsize(token_T *lst);
char	*ft_strchr(char *s, int c);
#endif