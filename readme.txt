pwd dawdawdwd (bash)


waitpid while;

√\bash-3.2$ exit 4654 46646 4646
exit
bash: exit: too many arguments
bash-3.2$ 
cat wow | echo 1

bash-3.2$ unset =
bash: unset: `=': not a valid identifier
bash-3.2$ unset /=
bash: unset: `/=': not a valid identifier
bash-3.2$ unset ;/=
bash: /=: No such file or directory
bash-3.2$ mkdir waw
bash-3.2$ cd waw
bash-3.2$ rm ../waw
rm: ../waw: is a directory
bash-3.2$ pwd
/Users/waboutzo/Desktop/minishell_ 2/waw
bash-3.2$ cd ..
bash-3.2$ 

bash-3.2$ unset =
bash: unset: `=': not a valid identifier
bash-3.2$ unset = PATH
bash: unset: `=': not a valid identifier
bash-3.2$ env
bash: env: No such file or directory
bash-3.2$ exit
exit
➜  minish

bash-3.2$ export / l=k
bash: export: `/': not a valid identifier
export d="dwadda"
➜  minishell_ 2 git:(main) ✗ export l="dwadda"
➜  minishell_ 2 git:(main) ✗ export s="dwadda"
➜  minishell_ 2 git:(main) ✗ export q="dwadda"
➜  minishell_ 2 git:(main) ✗ export z="dwadda"

export d      d=''(set)    



signal this case cat > l



minishell$ cat << l 
>da
>wd
>aw
>d
>aw
>daw
>d
>l
da
wd
aw
d
aw
daw
d
minishell$ da
minishell: da: command not found
minishell$ da
minishell: da: command not found
minishell$ cat << l 
>dwa
>d
>awd
>
>wa
>d
>l
dwa
d
awd

wa
d
minishell$ cat << l 
>daw
>d
>aw
>daw
>d
>w
>wa
>d
>aw
>d
>aw
>
>awa
>l
daw
d
aw
daw
d
export a+=b+=c+=d

export d+="ww"



char	*remove_qoutes(char *str)
{
	char	*value;
	char	*s;
	int		c[2];
	t_lexer	*lexer;
	char	*tmp;

	lexer = init_lexer(str);
	value = ft_calloc(1, sizeof(char));
	c[0] = '"';
	c[1] =  '\'';
	int	i = 0;
	while (lexer->c != '\0')
	{
		if(lexer->c == c[0] || lexer->c == c[1])
		{
			if(i == 0)
			{
				i++;
				c[0] = lexer->c;
				c[1] =  lexer->c;
			}
			else
			{
				c[0] = '"';
				c[1] =  '\'';
			}
			lexer_advance(lexer);
		}
		s = lexer_get_current_char_as_string(lexer);
		tmp = value;
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		free(tmp);
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	free(lexer);
	return (value);
}