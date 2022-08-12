/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:50:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/12 16:06:27 by waboutzo         ###   ########.fr       */
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
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_redirection
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
	char	*path;
}	t_redirec;

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}	t_node;

typedef struct s_args
{
	char	**after_expand;
	char	*value;
}	t_args;

typedef struct s_cmd
{
	enum
	{
		VALID,
		NOT_VALID,
	}e_rtype;
	t_redirec	*input;
	t_redirec	*output;
	char		**after_expand;
	t_node		*args;
	t_node		*redrec;
}	t_cmd;

typedef struct s_env_var
{
	enum
	{
		EXISTED,
		NOT,
	} e_stat;
	enum
	{
		SET_VALUE,
		CONCATENATE,
		NOTHING,
	} e_type;
	int		index;
	int		key;
	char	*name;
	char	*value;
}	t_env_var;

char		*g_cwd_saver;
int			ft_strlen(char *str);
void		*ft_calloc(int count, int size);
void		ft_bzero(void *s, int n);
char		*ft_strdup(const char *s1);
char		*ft_realloc(char *ptr, int size);
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
t_node		*ft_lstnew(void *content);
int			ft_isalpha(int c);
char		*ft_substr(char *s, int start, int len);
int			ft_isalnum(int c);
char		**ft_split(char *s, char c);
int			ft_isdigit(int c);
int			get_type(char *c);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_itoa(int n);
int			ft_atoi(const char *ptr);
char		*ft_strcat(char *dest, char *src);
char		**ft_strdup_double(char **ptr);
char		**join_double_pointer(char **str, char **ptr);
int			ft_counte_novide(char **str);
char		**advanced_split(char *str);
void		pure_after_expand(char **str, char **envp);
char		**join_args(t_node *head);
int			double_pointer_len(char **str);
int			get_key(char *s, int index);
char		**env_split(char **envp, int i);
void		init_array(int *i, int size);

char		*quotes_cases(t_lexer *lexer, char **envp, int c);
char		*dollar_value(char **envp, char *var);
char		*ft_norm(t_lexer *lexer);
int			get_index(t_lexer lexer, char c);
char		*handle_env_var(t_lexer *lexer, char **envp);
char		*pure_arg(char *str, char **envp);
void		here_doc(t_redirec *redirc, char **envp);
char		*quotes_handler(t_lexer *lexer, char **envp, int c);
char		*quotes(t_lexer *lexer, char **envp, int c);
void		set_to_defaults(char *str);
void		quotes_replace(char *str);
int			closed_qoutes(t_lexer *lexer, char c, int *bool);
void		*parsing(t_node **command, char **envp, int *index);
t_node		*handler(t_lexer *lexer);
void		remove_vide_string(char ***s);
void		remove_qoutes_delimiter(char **str);
void		parsing_args(t_node **head, char **envp);
int			here_doc_counter(t_node *head);
void		*parsing_redrection(t_node **head, char **envp, int *index);
void		open_heredoc_in_signle_cmd(t_node **head, char **envp);

t_redirec	*get_input(t_node *head);
t_redirec	*get_output(t_node *head);
void		ft_setter(int value);
void		error_handling(char *cmd);
char		*check_cmd(char *cmd, char **envp);
void		dup_norm(int fildes1, int fildes2);
int			is_built_ins(char **after_expand, char ***env, int flag);
int			is_directory(char *path);
void		printf_error(char *p, char *str, char *s);
char		**split_path(char *s, char c);
void		save_pwd(char *s);
int			ft_getter(void);
void		fork_failed(int *i, int index);
void		sig_handler(int sig);
t_cmd		*init_cmd(t_lexer *lexer, t_token **token);
int			ft_pipe_check(t_token *token, t_token *previous);
char		**sorted_env(char **env);
int			get_index_of_double_char(char **envp, char *var);
char		*getpwd(char **env);
int			ft_check_var_validition(char *s);
void		execution_multi_cmds(t_node *head, char **env);
void		execution_cmd(t_node *head, char ***env);
int			ft_check_ambiguous(t_redirec *redirc);
void		open_all_redrec(t_node **command);
char		*get_value(char *str);
void		*open_file_descriptor(t_node **head);

char		**my_envp(char **envp);
void		my_exit(char **str, int flag);
void		pwd(char **env);
void		print_env(char **envp, char **after_expand);
void		cd(char *path, char ***env);
void		echo(char **after_expand);
void		my_export(char ***env, char **vars);
void		unset(char ***envp, char **var);

void		free_double_char(char **tmp, int t);
void		free_args(t_node **head);
void		free_redirc(t_node **head);
void		free_node(t_node **head);
void		free_var(t_env_var *var);
void		*ft_free(t_token *token, t_lexer *lexer, t_node *node, t_node *tmp);

#endif
