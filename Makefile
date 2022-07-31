# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 11:25:03 by yojoundi          #+#    #+#              #
#    Updated: 2022/07/31 17:04:26 by waboutzo         ###   ########.fr        #
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

ECECUTION = built_ins execute_single_command execution_tools exit_code my_envp \
			execute execution_multi_commands exit export unset

UTILS = ft_atoi ft_isalpha ft_lstadd_back ft_lstdelone ft_lstsize ft_strcat ft_strdup \
		ft_isdigit ft_lstadd_front ft_lstlast ft_realloc ft_strchr ft_strjoin ft_strncmp \
		ft_calloc ft_itoa ft_lstclear ft_lstnew ft_split ft_strcmp ft_strlen ft_substr 

PARSING = advanced_split  dollar_parsing lexer2 print_function token\
		cmd  get_important_data parsing  quotes_parsing\
		delimiter_parsing  lexer  parsing_  redirection_file
SRCS =  $(addsuffix .c, $(addprefix src/libft_tools/, $(UTILS))) \
		$(addsuffix .c, $(addprefix src/execution/, $(ECECUTION))) \
		$(addsuffix .c, $(addprefix src/parsing/, $(PARSING))) \
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
