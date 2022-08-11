/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:26:39 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 02:14:08 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_line(char *s1, int rd)
{
	int		i;
	char	*p;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i] != '\n' && s1[i] != '\0')
		i++;
	p = ft_strldup(s1, i + 1);
	if (rd == 0 && ft_strlen(p) == 0)
	{
		free(p);
		return (NULL);
	}
	return (p);
}

char	*get_remember(char *s1)
{
	int		i;
	char	*p;

	i = 0;
	if (!s1)
		return (0);
	if (s1[0] == '\0')
	{
		free(s1);
		return (NULL);
	}
	while (s1[i] != '\0' && s1[i] != '\n')
		i++;
	i++;
	p = ft_strldup(s1 + i, ft_strlen(s1) - i + 1);
	free(s1);
	return (p);
}

char	*ft_free_buffer(char *buffer)
{
	free(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*line;
	static char		*save;
	int				rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	rd = 1;
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	buffer[0] = '\0';
	while (rd != 0 && !ft_strchr(buffer, '\n'))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd < 0)
			return (ft_free_buffer(buffer));
		buffer[rd] = '\0';
		save = ft_strjoin_beta(save, buffer);
	}
	free(buffer);
	line = get_line(save, rd);
	save = get_remember(save);
	return (line);
}

// #include <stdio.h>
// int main(void)
// {
//     int fd = open("text.txt",O_RDONLY);
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
//     printf("%s",get_next_line(fd));
// }
