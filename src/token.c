/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:03:03 by waboutzo          #+#    #+#             */
/*   Updated: 2022/05/28 15:29:02 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

token_T *init_token(int type, char *value)
{
	token_T *token;
	
	token = ft_calloc(1, sizeof(token_T));
	if(!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	token->previous = NULL;
	return (token);
}