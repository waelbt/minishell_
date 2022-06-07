/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:41:21 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/07 10:16:32 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "lexer.h"
# include "minishell.h"

typedef struct TOKEN_STRUCT
{
	enum
	{
		TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_REDICRECTION,
		TOKEN_ERROR,
		TOKEN_EOF,
	} e_type;
	char				*value;
	struct TOKEN_STRUCT	*previous;
	struct TOKEN_STRUCT	*next;
}	t_token;

t_token	*init_token(int type, char *value);
#endif