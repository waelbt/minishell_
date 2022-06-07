/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:02:54 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/07 19:30:15 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void free_args(t_args *args)
{
	free(args->value);
}

void free_redrection(t_redirec *redrec)
{
	free(redrec->file);
}

void free_node(t_cmd *cmd)
{
	ft_lstclear(&cmd->args, (void *)free_args);
	ft_lstclear(&cmd->redrec, (void *)free_redrection);
}