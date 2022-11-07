# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 15:04:45 by kiyoon            #+#    #+#              #
#    Updated: 2022/11/07 15:04:46 by kiyoon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = miniRT

LIBFT       = libft

LIBFT_LIB   = libft.a

SRCS        = ./main.c 

OBJS        = $(SRCS:.c=.o)

RM          = rm -f

LIBC        = ar rc

CC          = gcc

CFLAGS      = -Wall -Wextra -Werror #-g3 -fsanitize=address


$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	mv $(LIBFT)/$(LIBFT_LIB) .
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
all : $(NAME)

fclean : clean
	$(RM) $(NAME) $(LIBFT_LIB)
	make fclean -C $(LIBFT)

clean :
	$(RM) $(OBJS) 
	make clean -C $(LIBFT)

re : fclean all

.PHONY : all bonus clean clean re
