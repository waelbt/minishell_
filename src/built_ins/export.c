/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:13:02 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/24 20:30:43 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		get_j(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *) malloc((len + 1) * sizeof(char));
	if (!ptr)
	{
		return (0);
	}
	while (i < len)
	{
		if (i < ft_strlen(s1))
			*(ptr + i) = *(s1 + i);
		else if (i >= ft_strlen(s1))
			*(ptr + i) = *(s2++);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

void	free_double_char(char **tmp)
{
	int	i;

	i = 0;
	if(!tmp)
		return ;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}
/* strduppp*/
void	print_export(char **envp)
{
	int	i;
	
	i = 0;
	while(envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		len = 0;
	i = 0;
	if (len < slen)
		p = (char *)malloc((len + 1) * sizeof(char));
	else
		p = (char *)malloc((slen + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (s[start] && i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strchr(char *s, int c)
{
	size_t		i;
	char		*p;

	i = 0;
	p = (char *) s;
	while (i <= ft_strlen(s))
	{
		if (*(p + i) == (char )c)
			return (p + i);
		i++;
	}
	return (0);
}

void	right_value(char **str)
{
	char	*s;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	int		j;

	j = 0;
	if ((s = ft_strchr(*str, '=')))
		{
			tmp = ft_strjoin("\"", ++s);
			tmp1 = tmp;
			tmp = ft_strjoin(tmp, "\"");
			j = get_j(*str);
			*str = ft_substr(*str, 0, j+1);
			tmp2 = *str;
			free(tmp2);
		}
	else
		tmp = strdup("");
	*str = ft_strjoin(*str, tmp);
	free(tmp);
	free(tmp1);
}
	
void	my_export(char ***envp, char *value)
{
	int		i;
	char	**new_envp;

	i = 0;
	if (value == NULL)
		print_export(*envp);
	else
	{
		right_value(&value);
		while ((*envp)[i])
			i++;
		new_envp = (char **)calloc((i + 2), sizeof(char *));
		i = 0;
		while ((*envp)[i])
		{
			new_envp[i] = strdup((*envp)[i]);
			i++;
		}
		new_envp[i] = strdup(value);
		i++;
		new_envp[i] = NULL;
		*envp = new_envp;
		free(value);
	}
}

/* sort table in another table
 * if var hav no val don't add it to env*/
int main(int ac, char **av)
{
	int		i;
	char	**str;

	i = 0;
	my_export(&av, "so=me");
	while(av[i])
	{
		printf("```%s```\n", av[i]);
		i++;
	}
}

