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
		execute/builtin_cd1.c \
		execute/builtin_cd2.c \
		execute/builtin_env_pwd_echo_exit.c \
		execute/builtin_export1.c \
		execute/builtin_export2.c \
		execute/builtin_unset.c \
		execute/builtin.c \
		execute/error1.c \
		execute/error2.c \
		execute/exec_set.c \
		execute/exec_start.c \
		execute/heredoc.c \
		execute/path.c \
		execute/pipe_stream.c \
		execute/signal.c \
		execute/utils.c \
		Libft/ft_atoi.c \
		Libft/ft_isalpha.c \
		Libft/ft_isdigit.c \
		Libft/ft_itoa.c \
		Libft/ft_putchar_fd.c \
		Libft/ft_putstr_fd.c \
		Libft/ft_split.c \
		Libft/ft_strchr_idx.c \
		Libft/ft_strchr.c \
		Libft/ft_strcmp_exec.c \
		Libft/ft_strcmp.c \
		Libft/ft_strdup.c \
		Libft/ft_strjoin_no_free.c \
		Libft/ft_strjoin_exec.c \
		Libft/ft_strjoin.c \
		Libft/ft_strncmp_equal.c \
		Libft/ft_strncmp_exec.c \
		Libft/ft_substr.c \
		Libft/ft_trim.c \
		cmd_list_utils.c \
		delete_quotes.c \
		delete_quotes_utils.c \
		env_list_utils.c \
		exit_status.c \
		expanding_env.c \
		expanding_len_loc.c \
		expanding_str.c \
		expanding.c \
		free_utils.c \
		init_data.c \
		lexer_list_utils.c \
		lexer_token_ampersand.c \
		lexer_token_parenthesis.c \
		lexer_token_pipe.c \
		lexer_token_redirection.c \
		lexer_token_semicolon.c \
		lexer_token_word.c \
		lexer.c \
		parsing_command_split.c\
		parsing_command.c\
		parsing_get.c\
		parsing_set.c\
		parsing_heredoc.c\
		parsing_redirection.c\
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