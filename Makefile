# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 11:25:03 by yojoundi          #+#    #+#              #
#    Updated: 2022/08/01 13:00:40 by waboutzo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INC = -I include
RM = rm -rf
MYDIR= objects_files
CC = cc
CFLAGS = -Wall -Wextra -Werror -I /Users/${USER}/.brew/opt/readline/include #-g -fsanitize=address
OBJ=$(SRCS:.c=.o)
OBJBONUS=$(SRCBONUS:.c=.o)

BUILT_INS	=	cd echo env exit export pwd unset

ECECUTION	=	execute_single_command execution_tools\
				execute execution_multi_commands exit_code

LEXER		=	get_tokens lexer lexer2 token

UTILS		=	ft_atoi ft_isalpha ft_lstadd_back ft_lstdelone ft_lstsize ft_strcat ft_strdup \
				ft_isdigit ft_lstadd_front ft_lstlast ft_strchr ft_strjoin ft_strncmp \
				ft_calloc ft_itoa ft_lstclear ft_lstnew ft_split ft_strcmp ft_strlen ft_substr 

PARSING		=	advanced_split  dollar_parsing  print_function \
		   		get_important_data parsing  quotes_parsing\
				delimiter_parsing  parsing_  redirection_file

SRCS =  $(addsuffix .c, $(addprefix src/libft/, $(UTILS))) \
		$(addsuffix .c, $(addprefix src/execution/, $(ECECUTION))) \
		$(addsuffix .c, $(addprefix src/parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix src/lexer_tokens/, $(LEXER))) \
		$(addsuffix .c, $(addprefix src/built_ins/, $(BUILT_INS))) \
		src/free_node.c
.c.o:
	@$(CC)  $(CFLAGS) $(INC) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJ)
	@$(CC)  $(CFLAGS) $(OBJ) $(INC) main.c -L /Users/${USER}/.brew/opt/readline/lib  -lreadline  -o $(NAME)
# @[ -d $(MYDIR) ] || mkdir -p $(MYDIR)
# @mv $(OBJ) objects_files

clean :
	@$(RM) $(OBJ) $(MYDIR)

fclean : clean
	@$(RM) $(NAME) 

re : fclean all

.PHONY:			all clean fclean re bonus
