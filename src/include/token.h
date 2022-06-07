/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:41:21 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/07 11:34:03 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "lexer.h"
# include "minishell.h"

typedef struct s_token
{
	enum
	{
		TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_REDICRECTION,
		TOKEN_EOF,
		TOKEN_ERROR,
	} e_type;
	char				*value;
}	t_token;

t_token	*init_token(int type, char *value);
#endif