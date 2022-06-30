/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:50:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/30 13:02:26 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include "lexer.h"
# include "token.h"
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct redirection
{
	int		fd;
	enum
	{
		INPUT,
		OUTPUT,
		APPEND,
		HERE_DOC,
		ERROR,
	}e_rtype;
	char	*file;
	char	**after_expand;
}	t_redirec;

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;

typedef struct args
{
	char	**after_expand;
	char	*value;
}	t_args;

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
t_redirec	*init_redirection(t_token **token, t_lexer *lexer);
void		printf_args(t_node *head);
void		printf_redrection(t_node *head);
void		printf_node(t_node *head);
char		*ft_strdup(const char *s1);
void		free_node(t_node **head);
t_cmd		*init_cmd(t_lexer *lexer, t_token **token);
void		dda(t_node **head);
void		fed(t_node **head);
char		*dollar_value(char **envp, char *var);
void		*parsing(t_node **command, char **envp, int *index);
int			get_type(char *c);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*pure_arg(char *str, char **envp);
int			ft_isalnum(int c);
char		**ft_split(char *s, char c);
int			ft_isdigit(int c);
int			find_char(char *s, char c);
char		*handle_env_var_case(t_lexer *lexer, char **envp);
char		*handle_env_var(t_lexer *lexer, char **envp);
int			get_index(t_lexer lexer, char c);
char		*hard_code(t_lexer *lexer, char **envp, int c, int next_qoutes);
char		*env_var_inside_qoutes(t_lexer *lexer, char **envp, int c);
char		*quotes_handler(t_lexer *lexer, char **envp, int c);
char		*quotes_cases(t_lexer *lexer, char **envp, int c);
char		*ft_norm(t_lexer *lexer);
char		*delimiter(char *str, char **envp);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			open_file_descriptor(t_redirec	*redrec, char **envp, int *index);
void		free_double_char(char **tmp, int t);
// void		execution(t_cmd *cmd);
char		*ft_itoa(int n);
char		**advanced_split(char *str);
char		*quotes(t_lexer *lexer, char **envp, int c);
void		init_array(int *i, int size);
int			double_pointer_len(char **str);
char		*remove_qoutes(char *str);
void		pure_after_expand(char **str);
int			ft_counte_novide(char **str);
t_redirec	*get_output_input(t_node *head, int t);
char		*check_acces(char *cmd, char **envp);
char		*invalid_command_error(char *cmd, char *path);
char		*get_path(char **envp);
t_redirec	*ft_close(t_node *head);
char		**join_args(t_node *head);
char		*check_cmd(char *cmd, char **envp);
void		*execution(t_node *head, char **env);
#endif
