/*HEADER*/
/*HEADER*/
/*HEADER*/
/*HEADER*/
#include "../include/minishell.h"


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

void	pwd(char **envp)
{
	char	**tmp;

	while (*envp)
	{
		tmp = ft_split(*envp, '=');
		if (!ft_strcmp(tmp[0], "PWD"))
		{
			printf("%s\n", tmp[1]);
		}
		free_double_char(tmp);
		envp++;
	}
}
int main(int ac, char **av, char **envp)
{
		pwd(envp);
}
