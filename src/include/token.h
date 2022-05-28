/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:41:21 by waboutzo          #+#    #+#             */
/*   Updated: 2022/05/28 15:25:54 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "lexer.h"
#include "minishell.h"

typedef struct TOKEN_STRUCT
{
    enum
    {
        TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_OUTPUT,
		TOKEN_INPUT,
        TOKEN_ERROR,
        TOKEN_HERE_DOC
    } type;
    char				*value;
    struct TOKEN_STRUCT	*previous;
    struct TOKEN_STRUCT	*next;
} token_T;

token_T *init_token(int type, char *value);
#endif