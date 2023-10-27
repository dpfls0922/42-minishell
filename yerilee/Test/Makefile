# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yerilee <yerilee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 20:14:31 by yerilee           #+#    #+#              #
#    Updated: 2023/10/13 20:14:31 by yerilee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c\
		Libft/ft_strcmp.c \
		Libft/ft_strjoin.c \
		Libft/ft_substr.c \
		Libft/ft_trim.c \
		env_list_utils.c \
		expanding_env.c \
		expanding_len_loc.c \
		expanding_str.c \
		expanding.c \
		init_data.c \
		lexer_list_utils.c \
		lexer_token_ampersand.c \
		lexer_token_parenthesis.c \
		lexer_token_pipe.c \
		lexer_token_redirection.c \
		lexer_token_semicolon.c \
		lexer_token_word.c \
		lexer.c \
		parsing_cmd_list_utils.c\
		parsing_cmd_split.c\
		parsing_del_redirection.c\
		parsing_get.c\
		parsing_set.c\
		parsing_heredoc.c\
		parsing.c\
		syntax_pipe.c \
		syntax_quotes.c \
		syntax_redirection.c \
		syntax.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus