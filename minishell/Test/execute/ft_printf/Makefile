# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spark2 <spark2@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 16:11:17 by spark2            #+#    #+#              #
#    Updated: 2023/11/17 20:26:26 by spark2           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS :=
SRCS += ft_printf.c
SRCS += ft_strlen_printf.c
SRCS += ft_putchar.c
SRCS += ft_putstr.c
SRCS += print_c_s_p_per.c
SRCS += print_d_i_u_x.c

OBJS = $(SRCS:.c=.o)

INCLUDE = ft_printf.h

CC = cc -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rc $@ $^

%.o : %.c
	$(CC) -c $< -o $@ -I $(INCLUDE)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
