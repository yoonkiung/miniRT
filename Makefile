# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 15:04:45 by kiyoon            #+#    #+#              #
#    Updated: 2022/11/15 19:13:21 by daechoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = miniRT

LIBFT       = libft

LIBFT_LIB   = libft.a

SRCS        =./main.c \
				vector/vector3_1.c vector/vector3_2.c \
				trace/camera.c trace/ray.c trace/light.c \
				parse/init_mlx.c parse/initalization.c parse/parse_A.c parse/parse_C.c parse/parse_L.c parse/parse_plane.c parse/parse_cylinder.c parse/parse_sphere.c \
				util/util1.c \
				select/modify.c select/select.c \
				figure/plane.c figure/sphere.c

OBJS        = $(SRCS:.c=.o)

RM          = rm -f

LIBC        = ar rc

CC          = gcc

CFLAGS      = -Wall -Wextra -Werror #-g3 -fsanitize=address

MLX			= -L./mlx -lmlx -framework OpenGL -framework AppKit

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	mv $(LIBFT)/$(LIBFT_LIB) .
	$(CC) $(CFLAGS) $(MLX) -o $(NAME) $(OBJS) $(LIBFT_LIB)

.c.o: $(SRC)
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
