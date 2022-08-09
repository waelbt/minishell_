/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:50:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/08 19:03:24 by waboutzo         ###   ########.fr       */
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
# define BUFFER_SIZE 1
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
	char	*path;
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

typedef struct env_var
{
	enum
	{
		EXISTED,
		NOT,
	} t_stat;
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

char		*cwd_saver;
int			ft_strlen(char *str);
void		*ft_calloc(int count, int size);
void		ft_bzero(void *s, int n);
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
void		free_args(t_node **head);
void		free_redirc(t_node **head);
int			ft_isalpha(int c);
char		*dollar_value(char **envp, char *var);
void		*parsing(t_node **command, char **envp, int *index);
int			get_type(char *c);
char		*ft_substr(char *s, int start, int len);
char		*pure_arg(char *str, char **envp);
int			ft_isalnum(int c);
char		**ft_split(char *s, char c);
int			ft_isdigit(int c);
char		*handle_env_var_case(t_lexer *lexer, char **envp);
char		*handle_env_var(t_lexer *lexer, char **envp);
int			get_index(t_lexer lexer, char c);
char		*hard_code(t_lexer *lexer, int next_qoutes);
char		*env_var_inside_qoutes(t_lexer *lexer, char **envp, int c);
char		*quotes_handler(t_lexer *lexer, char **envp, int c);
char		*quotes_cases(t_lexer *lexer, char **envp, int c);
char		*ft_norm(t_lexer *lexer);
char		*delimiter(char *str, char **envp);
int			ft_strncmp(const char *s1, const char *s2, int n);
void		*open_file_descriptor(t_node **head);
void		free_double_char(char **tmp, int t);
// void		execution(t_cmd *cmd);
char		*ft_itoa(int n);
void		dup_norm(int fildes1, int fildes2);
char		**advanced_split(char *str);
char		*quotes(t_lexer *lexer, char **envp,int c);
void		init_array(int *i, int size);
int			double_pointer_len(char **str);
char		*remove_qoutes(char *str, char **envp);
void		pure_after_expand(char **str, char **envp);
int			ft_counte_novide(char **str);
void		check_acces(char **cmd, char **envp);
char		*invalid_command_error(char *cmd, char *path, char **paths);
char		*get_path(char **envp);
void		ft_close(t_node *head);
char		**join_args(t_node *head);
void		check_cmd(char **cmd, char **envp);
void		execution(t_node *head, char ***env);
int			get_index_of_double_char(char **envp, char *var);
void		rl_replace_line (const char *text, int clear_undo);
void		sig_handler(int sig);
char		**ft_strdup_double(char **ptr);
void		here_doc(t_redirec *redirc, char **envp);
int			execute(char **after_expand, char ***env, int flag);
void		my_exit(char **str, int flag);
void		pwd(char **env);
void		print_env(char **envp, char **after_expand);
void		cd(char *path, char ***env);
void		echo(char **after_expand);
void		my_export(char ***env, char **vars);
int			ft_atoi(const char *ptr);
void		unset(char ***envp, char **var);
void		rl_replace_line (const char *text, int clear_undo);
int			ft_getter(void);
void		ft_setter(int value);
void		printf_error(char *p, char *str, char *s);
void		execution_cmd(t_node *head, char ***env);
void		execution_multi_cmds(t_node *head, char **env);
int			execve(const char *path, char *const argv[], char *const envp[]);
int			ft_check_var_validition(char *s);
int			get_index_of_double_char(char **envp, char *var);
char 		*ft_strcat(char *dest, char *src);
t_node		*handler(t_lexer *lexer);
void		*ft_free(t_token *token, t_lexer *lexer, t_node *node, t_node *tmp);
int			ft_pipe_check(t_token *token, t_token *previous);
char		**join_double_pointer(char **str, char **ptr);
void		set_to_defaults(char *str);
void		quotes_replace(char *str);
int			get_key(char *s, int index);
char		**sorted_env(char **env);
char		**env_split(char **envp, int i);
void		free_var(t_env_var *var);
t_redirec	*get_input(t_node *head);
t_redirec	*get_output(t_node *head);
char		*getpwd(char **env);
char		**my_envp(char **envp);
char		*get_next_line(int fd);
char		*ft_strldup(const char *s1, int len);
char		*ft_strjoin_beta(char *s1, char *s2);
char		**split_path(char *s, char c);
void		error_handling(char *cmd, int flag);
int 		is_directory(const char *path);
#endif
