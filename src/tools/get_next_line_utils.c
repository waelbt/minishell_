/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:23:58 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/07 16:57:08 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin_beta(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strldup("", 0);
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	while (s1[++i])
		p[j++] = s1[i];
	i = -1;
	while (s2[++i])
		p[j++] = s2[i];
	p[j] = '\0';
	free(s1);
	return (p);
}

char	*ft_strldup(const char *s1, int len)
{
	char	*p;
	int		i;

	if (!s1)
		return (0);
	p = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!p)
		return (NULL);
	while (s1[i] && i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
