/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lol.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:25:45 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/07 17:27:06 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include"

int main(int ac, char **av, char **envp)
{
	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}
