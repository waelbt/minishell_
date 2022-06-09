/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <lchokri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:13 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/09 19:30:56 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_isalnum(int c)
{
	if (c <= '9' && c >= '0' )
		return (1);
	if (c <= 122 && c >= 97)
		return (1);
	if (c <= 90 && c >= 65)
		return (1);
	return (0);
}

void	expand_dollar(char *tmp, char **expd, int i)
{
	int	j;

	j = 0;
	while (ft_isalnum(tmp[i + 1]) || tmp[i + 1] == '_')
	{
		j++;
		i++;
	}
	*expd = malloc(j * sizeof(char *));
	(*expd)[j--] = '\0';
	while(j > -1)
	{
		(*expd)[j] = tmp[i];
		j--;
		i--;
	}
}

void pure_arg(char **str)
{
	int		i;
	char	*tmp;
	char	*expd;

	tmp = *str;
	i = 0;
	while(tmp[i])
	{
		if (tmp[i] == '$')
		{
			expand_dollar(tmp, &expd, i);
//			= expd;
			free(expd);
		}
		i++;
	}
}
void parsing_args(t_node **head)
{
	t_node		*temporary;

	temporary = *head;
	while (temporary != NULL)
	{
		pure_arg(&((t_args *) temporary->content)->value);
		temporary = temporary->next;
	}
}

// void parsing_redrection(t_node **head)
// {
// 	t_node		*temporary;

// 	temporary = *head;
// 	while (temporary != NULL)
// 	{
// 		temporary = temporary->next;
// 	}
// }

void parsing(t_node **command, char **envp)
{
	t_node	*temporary;

	temporary = *command;
	while (temporary != NULL)
	{
		parsing_args(&((t_cmd *)temporary->content)->args);
		// parsing_redrection(&((t_cmd *)temporary->content)->redrec);
		temporary = temporary->next;
	}
}
