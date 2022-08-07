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

 ls | << $d | wc




 minishell$ export d="'echo salam'"
minishell$ $d
minishell: 'echo: command not found
minishell$ export d="salam  "
minishell$ $d
=================================================================
==73412==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x6020000076a0 at pc 0x000100b3c616 bp 0x7ffeef0d12b0 sp 0x7ffeef0d12a8
WRITE of size 8 at 0x6020000076a0 thread T0
    #0 0x100b3c615 in advanced_split advanced_split.c:95
    #1 0x100b41a04 in parsing_args parsing.c:46
    #2 0x100b4292d in parsing parsing.c:174
    #3 0x100b47122 in main main.c:94
    #4 0x7fff5b7ed3d4 in start (libdyld.dylib:x86_64+0x163d4)

0x6020000076a0 is located 0 bytes to the right of 16-byte region [0x602000007690,0x6020000076a0)
allocated by thread T0 here:
    #0 0x100bf5793 in wrap_malloc (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x61793)
    #1 0x100b3be88 in advanced_split advanced_split.c:79
    #2 0x100b41a04 in parsing_args parsing.c:46
    #3 0x100b4292d in parsing parsing.c:174
    #4 0x100b47122 in main main.c:94
    #5 0x7fff5b7ed3d4 in start (libdyld.dylib:x86_64+0x163d4)

export d w z z q 


//// echo $"PATH"

/// export d=h  E"C""$d"'o' hhhhh

///// exit dont exitwith flags


minishell$ <<f <<g
>fff
>ff
>f
minishell$ exit

cat > out1 < Makefile < dfjkhgs > 8  << l | echo > out hello << l | wc -l > 9  < dksjjksad

at > out1 < Makefile < dfjkhgs > 8  << l | echo > out hello << l | wc -l > 9  < dksjjksad | cat

leaks in herdoc

bash: $lsfw: ambiguous redirect
◦ env with no options or arguments



-x _="/Users/waboutzo/Desktop/mini/./minishell"
declare -x d=""
declare -x x="rwrw"
declare -x x1="242"
declare -x x2="wjrwlj"
minishell$ export x=1
minishell$ ]\
minishell: ]\: command not found
minishell$ export x="ls"
minishell$ $x
Makefile        main.c          readme.txt      src
a               minishell       ruin_my_code.c
minishell$ export x="ls -a"
minishell$ $x
.               .vscode         main.c          ruin_my_code.c
..              Makefile        minishell       src
.git            a               readme.txt
minishell$ ./3a
minishell: ./3a: command not found
minishell$ ./a
minishell: ./a: command not found
minishell$ 


leaks Report Version: 4.0
Process 7571: 588 nodes malloced for 319 KB
Process 7571: 7 leaks for 176 total leaked bytes.

    7 (176 bytes) ROOT LEAK: 0x7fded6d00c60 [32]
       5 (128 bytes) 0x7fded6d00c20 [32]
          3 (80 bytes) 0x7fded6d00c00 [32]
             1 (32 bytes) 0x7fded6f00440 [32]
             1 (16 bytes) 0x7fded6d00b20 [16]  length: 1  " "
          1 (16 bytes) 0x7fded6d00b60 [16]  length: 1  "s"
       1 (16 bytes) 0x7fded6d00c40 [16]  length: 1  "l"

minishell$ cat << lim
>'$USER'
>lim
'$USER'

bash-3.2$ cat << lim
> '$USER'
> lim
'waboutzo'



minishell$ mkdir p
minishell$ cd p/
minishell$ pwd
/Users/waboutzo/Desktop/mini/p
minishell$ rm -rf ../p/
minishell$ pwd
/Users/waboutzo/Desktop/mini/p
minishell$ unset PWD
minishell$ pwd
failed to get the current working directory
minishell$ cd ..
AddressSanitizer:DEADLYSIGNAL

use chdir, fchdir -- change current working director


/// unset PWD; cd dir; OLDPWD=""
/// unset PWD; cd dir; cd ..; OLDPWD="dirPAth"
/// unset PWD OLDPWD; ....
/// cd to home


i fix pipe leaks (tay i3awd itssti liya chi wa7d fe darari)


cd src/
unset PWD
mkdir p
cd p
rm -rf ../p
cd
cd ..
export
export | grep PWD


    10 (256 bytes) ROOT LEAK: 0x7fb17df00120 [32]
       8 (208 bytes) 0x7fb17df000e0 [32]
          6 (160 bytes) 0x7fb17dc044e0 [32]
             4 (112 bytes) 0x7fb17dc044b0 [32]
                3 (80 bytes) 0x7fb17de00130 [32]
                   1 (32 bytes) 0x7fb17de00100 [32]
                   1 (16 bytes) 0x7fb17de00120 [16]  length: 1  "l"
             1 (16 bytes) 0x7fb17dc044d0 [16]  length: 1  "p"
          1 (16 bytes) 0x7fb17df00110 [16]  length: 1  "x"
       1 (16 bytes) 0x7fb17df00100 [16]  length: 1  "e"