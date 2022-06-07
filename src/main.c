/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:48:37 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/07 15:38:28 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void printf_args(t_node *head)
{
	t_node *temporary = head;
	t_args *tmp;

    while(temporary != NULL)
    {
		tmp = (t_args *) temporary->content;
        printf("[arg : %s] -> ", tmp->value);
        temporary = temporary->next;
    }
    printf("\n");
}

void printf_redrection(t_node *head)
{
	t_node *temporary = head;
	t_redirec *tmp;

    while(temporary != NULL)
    {
		tmp = (t_redirec *) temporary->content;
        printf("[type : %d, file: %s ]->",tmp->e_rtype, tmp->file);
        temporary = temporary->next;
    }
    printf("\n");
}

void printf_node(t_node *head)
{
	t_node *temporary = head;
	t_cmd *cmd;
	int i;

    i = 0;
	while(temporary != NULL)
   	{
		printf("cmd number :%d\n", i++);
		cmd = (t_cmd *)temporary->content;
		printf_args(cmd->args);
		printf("\n");
		printf_redrection(cmd->redrec);
        temporary = temporary->next;
    }
}

t_node	*handler(char *str)
{
	t_lexer *lexer;
	t_token *token;
	t_node	*node;
	t_node	*tmp;
	
	tmp = NULL;
	lexer = init_lexer(str);
	token = lexer_get_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		if(token->e_type == TOKEN_EOF)
			return (NULL);
		node = ft_lstnew((void *)init_cmd(lexer, token));
		ft_lstadd_back(&tmp, node);
		token = lexer_get_next_token(lexer);
	}
	node = tmp;
	printf_node(node);
	free(token);
	free(lexer);
	return (node);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_node	*cmd;

	(void) envp;

	if (argc == 1)
	{
		while (1)
		{
			str = readline("\033[0;35mminishell$ \033[0;37m");
			add_history (str);
			cmd = handler(str);
			free(str);
		}
	}
	return (0);
}


// token = handler(str);
// print_linked_list(token);