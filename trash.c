int ft_counter(t_lexer lexer, int c)
{
	int counter;

	counter = 0;
	while(lexer.c != '\0')
	{
		if(lexer.c == c)
			counter++;
		lexer_advance(&lexer);
	}
	return counter;
}

int get_index(t_lexer lexer, int c)
{
	while(lexer.c != '\0')
	{
		if(lexer.c == c)
			return (lexer.i);
		lexer_advance(&lexer);
	}
	return (lexer.i);
}

int get_first(t_lexer lexer)
{
	while(lexer.c != '\0')
	{
		if (lexer.c == 34)
			return (34);
		if (lexer.c == 39)
			return (39);
		lexer_advance(&lexer);
	}
	return (0);
}

int get_quotes_index(t_lexer lexer, int c, int index)
{
	int h;
	lexer.i = index;
	lexer.c = lexer.contents[lexer.i];
	lexer_advance(&lexer);
	h = (((c == 34) * 39) + ((c == 39) * 34));
	while (lexer.c != '\0')
	{
		if(lexer.c == c)
		{
			lexer_advance(&lexer);
			if(lexer.c == h)
			{
				if((ft_counter(lexer, h) % 2))
					return (-1);
				else
					return (lexer.i - 1);
			}
			if(lexer.c == c)
				return (lexer.i - 1);
			if(lexer.c == 32 || lexer.c == '\0')
				return (lexer.i - 1);
			while(lexer.c != 32 && lexer.c != '\0')
			{
				// printf("%c",lexer.c);
				lexer_advance(&lexer);
			}
			return (lexer.i);
		}
		lexer_advance(&lexer);
	}
	return (0);
}

// t_token	*lexer_collect_quotes(t_lexer *lexer, int c, int h)
// {
// 	int		len;
// 	char	*value;
// 	char	*s;

// 	value = ft_calloc(1, sizeof(char));
// 	lexer_advance(lexer);
// 	len = get_index(*lexer, c, h);
// 	if (len < 0)
// 		return (init_token(TOKEN_ERROR, ""));
// 	while (lexer->i < len)
// 	{
// 		if (lexer->c == c)
// 			lexer_advance(lexer);
// 		s = lexer_get_current_char_as_string(lexer);
// 		value = ft_realloc(value, (ft_strlen(value)
// 					+ ft_strlen(s) + 1) * sizeof(char));
// 		ft_strcat(value, s);
// 		free(s);
// 		lexer_advance(lexer);
// 	}
// 	lexer_advance(lexer);
// 	if (count_element(value, c, ft_strlen(value)) % 2 != 0)
// 		return (init_token(TOKEN_ERROR, ""));
// 	return (init_token(TOKEN_STRING, value));
// }
