/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:13:02 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/23 22:13:47 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

		//value should be splited only from the first '=', join 
		//double quotes in the beg and ending pejjj so annoying

void	right_value(char **str)
{
	char	*s;
	char	*tmp;

	if ((s = ft_strchr(*str, '=')))
		{
			tmp = ft_strjoin("\"", ++s);
			tmp = ft_strjoin(tmp, "\"");
		}
	*str = 
	*str = strdup(tmp);
	printf("str === %s\n", *str);
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
		printf("val before: %s\n", value);
		right_value(&value);
		printf("-------------------------------------------------------\n");
		printf("val after: %s\n", value);
		while ((*envp)[i])
			i++;
		new_envp = (char **)malloc((i + 1) * sizeof(char *));
		i = 0;
		while ((*envp)[i])
		{
			new_envp[i] = strdup((*envp)[i]);
			i++;
		}
		new_envp[i] = strdup(value);
		new_envp[++i] = NULL;
		/*old envp need to be freed*/
		*envp = my_envp(new_envp);
	}
}

int main(int ac, char **av)
{
	int		i;

	(void)ac;
	i = 0;
	my_export(&av, "some=var");
	while(av[i])
	{
		printf("```%s```\n", av[i]);
		i++;
	}
}

