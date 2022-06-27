exec	=	minishell

sources =	$(wildcard src/*.c) $(wildcard src/libft_tools/*.c)

objects =	$(sources:.c=.o)

flags	= 	-Wall -Wextra -Werror -lreadline 

CC		=	gcc

RM		= 	rm -f


all :	$(exec)
	make clean

$(exec)	: $(objects)
	$(CC) $(objects) $(flags) -o $(exec)

%.o	: %.c include/minishell.h
	$(CC) -c $(flags) %< -o $@

clean	:
	$(RM) src/*.o
	$(RM) src/libft_tools/*.o

fclean : clean
	$(RM) $(exec)

re : fclean all
