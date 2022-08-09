/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:23:31 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/01 15:07:18 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_to_defaults(char *str)
{
	int j = 0;
	while(str[j])
	{
		if(str[j] == -1)
			str[j] = '\'';
		if(str[j] == -2)
			str[j] = '"';
		j++;
	}
}

void 	quotes_replace(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '\'')
			str[i] = -1;
		if(str[i] == '"')
			str[i] = -2;
		i++;
	}
}

int	get_key(char *s, int index)
{
	int	key;

	if (!s[index])
		key = 0;
	if (s[index] == '=')
		key = 1;
	if (s[index] == '+')
		key = 2;
	return (key);
}

int	get_index(t_lexer lexer, char c)
{
	while (lexer.c != '\0')
	{
		if (lexer.c == c)
			return (lexer.i);
		lexer_advance(&lexer);
	}
	return (-1);
}

int	get_type(char *c)
{
	if (!ft_strcmp(c, "<"))
		return (0);
	else if (!ft_strcmp(c, ">"))
		return (1);
	else if (!ft_strcmp(c, ">>"))
		return (2);
	else if (!ft_strcmp(c, "<<"))
		return (3);
	return (-1);
}