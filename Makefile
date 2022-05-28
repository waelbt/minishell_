exec	=	minishell

sources =	$(wildcard src/*.c)

objects =	$(sources:.c=.o)

flags	= 	-Wall -Wextra -Werror -lreadline -g

CC		=	gcc

RM		= 	rm -f


all :	$(exec)

$(exec)	: $(objects)
	$(CC) $(objects) $(flags) -o $(exec)

%.o	: %.c include/minishell.h
	$(CC) -c $(flags) %< -o $@

clean	:
	$(RM) src/*.o

fclean : clean
	$(RM) $(exec)

re : fclean all