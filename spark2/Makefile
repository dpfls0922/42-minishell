NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L ./libft -lft

$(LIBFT):
	make -C ./libft all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus