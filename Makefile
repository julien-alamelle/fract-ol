# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalamell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 13:18:09 by jalamell          #+#    #+#              #
#    Updated: 2021/12/29 12:54:01 by jalamell         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRC_DIR=src/
OBJ_DIR=obj/
FILES=main hsl_to_rgb
SRC=$(addprefix $(SRC_DIR),$(addsuffix .c,$(FILES)))
OBJ=$(addprefix $(OBJ_DIR),$(addsuffix .o,$(FILES)))
NAME=out
FRAMEWORK=-framework OpenGL -framework AppKit
MLX_DIR=minilibx/
MLX=$(addprefix $(MLX_DIR), libmlx.a)
all: $(NAME)

clean:
	rm -f $(OBJ) $(OBJ_B)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX)

re: fclean all

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile $(MLX)
	$(CC) $(CFLAGS) -I ./minilibx/ -o $@ -c $<

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L ./minilibx/ -l mlx $(FRAMEWORK) -lm -o $(NAME)

$(MLX):
	@make -C $(MLX_DIR) 

.PHONY: all clean fclean re
