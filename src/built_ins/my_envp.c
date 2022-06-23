/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:27:46 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/22 21:47:21 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		get_size(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**my_envp(char **envp)
{
	char	**my_envp;
	int		i;
	int		j;

	j = 0;
	i = get_size(envp);
	my_envp = malloc(i+1 * sizeof(char *));
	while (envp[j])
	{
		my_envp[j] = strdup(envp[j]);
		j++;
	}
	return (my_envp);
}

int main(int ac, char **av)
{
	char	**my_av;
	int		i;

	i = 0;
	my_av = my_envp(av);

	while(my_av[i])
	printf("%s", my_av[i++]);
}
