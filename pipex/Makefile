src = pipex.c ft_calloc.c ft_split.c ft_strdup.c  ft_strjoin.c ft_strncmp.c 

obj = $(src:.c=.o)

exec = pipex

flags = -Wall -Wextra -Werror

CC = gcc

$(exec) : $(obj)
	$(CC) $(flags) $(obj) -o $(exec)

clean : 
	rm -rf *.o
