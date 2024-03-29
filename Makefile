# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/12 15:51:30 by waboutzo          #+#    #+#              #
#    Updated: 2022/08/13 23:03:40 by waboutzo         ###   ########.fr        #
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

TOOLS		=	advanced_split double_pointer_lib free_node print_function tools\
				path_split

ECECUTION	=	execute_single_command tools toolsII\
				is_built_ins execution_multi_commands exit_code

LEXER		=	get_tokens lexer lexer2 token

LIBFT		=	ft_atoi ft_isalpha ft_lstadd_back ft_lstdelone ft_lstsize ft_strcat ft_strdup \
				ft_isdigit ft_lstadd_front ft_lstlast ft_strchr ft_strjoin ft_strncmp \
				ft_calloc ft_itoa ft_lstclear ft_lstnew ft_split ft_strcmp ft_strlen ft_substr

PARSING		=	dollar_parsing quotes_parsing redirection_file  parsing_ii \
		   		get_important_data parsing_i parsing_iv parsing_v parsing_iii\

SRCS =  $(addsuffix .c, $(addprefix src/libft/, $(LIBFT))) \
		$(addsuffix .c, $(addprefix src/execution/, $(ECECUTION))) \
		$(addsuffix .c, $(addprefix src/parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix src/lexer_tokens/, $(LEXER))) \
		$(addsuffix .c, $(addprefix src/built_ins/, $(BUILT_INS))) \
		$(addsuffix .c, $(addprefix src/tools/, $(TOOLS)))
.c.o:
	@$(CC)  $(CFLAGS) $(INC) -c $< -o $@
	@stty -echoctl

all : $(NAME)

$(NAME): $(OBJ)
	@$(CC)  $(CFLAGS) $(OBJ) $(INC) main.c -L /Users/${USER}/.brew/opt/readline/lib  -lreadline  -o $(NAME)
	@stty -echoctl

clean :
	@$(RM) $(OBJ) $(MYDIR)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY:			all clean fclean re bonus
