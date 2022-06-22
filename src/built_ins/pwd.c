


void	pwd(char **envp)
{
		//still need to do smth about s size
	char s[111];

	printf("%s\n", getcwd(s, 111));
}

int main(int ac, char **av, char **envp)
{
		pwd(envp);
}
