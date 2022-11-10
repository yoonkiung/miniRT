# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 15:04:45 by kiyoon            #+#    #+#              #
#    Updated: 2022/11/10 19:25:49 by daechoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = miniRT

LIBFT       = libft

LIBFT_LIB   = libft.a

SRCS        = main.c vector3_1.c vector3_2.c camera.c parse_A.c parse_C.c parse_L.c parse_plane.c parse_cylinder.c parse_sphere.c util1.c ray.c light.c \
				initalization.c

OBJS        = $(SRCS:.c=.o)

RM          = rm -f

LIBC        = ar rc

CC          = gcc

CFLAGS      = -Wall -Wextra -Werror -g3 -fsanitize=address

MLX			= -L./mlx -lmlx -framework OpenGL -framework AppKit

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	mv $(LIBFT)/$(LIBFT_LIB) .
	$(CC) $(CFLAGS) $(MLX) -o $(NAME) $(OBJS) $(LIBFT_LIB)

.c.o: $(SRC)
	$(CC) $(CFLAGS) -c $^

all : $(NAME)

fclean : clean
	$(RM) $(NAME) $(LIBFT_LIB)
	make fclean -C $(LIBFT)

clean :
	$(RM) $(OBJS) 
	make clean -C $(LIBFT)

re : fclean all

.PHONY : all bonus clean clean re
