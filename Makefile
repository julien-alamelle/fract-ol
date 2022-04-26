# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalamell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 13:18:09 by jalamell          #+#    #+#              #
#    Updated: 2022/04/26 19:26:15 by jalamell         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g3 -I $(INCL_DIR)

SRC_DIR=src
OBJ_DIR=.obj
INCL_DIR=incl

FILES=main hsl_to_rgb data fractal cpx input hook
FILES_CL=main hsl_to_rgb data fractal cpx input hook
HEADER=fractol_struct fractol
HEADER_CL=fractol_struct fractol

SRC=$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(FILES)))
OBJ=$(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(FILES)))
HEAD=$(addprefix $(INCL_DIR)/,$(addsuffix .h,$(HEADER)))
NAME=out

FRAMEWORK=-framework OpenGL -framework AppKit -framework OpenCL
MLX_DIR=minilibx
MLX=$(addprefix $(MLX_DIR)/, libmlx.a)
all: $(NAME)

clean:
	rm -Rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile $(HEAD)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(MLX_DIR) -o $@ -c $<

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L $(MLX_DIR) -l mlx $(FRAMEWORK) -lm -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MLX):
	@make -C $(MLX_DIR) 

.PHONY: all clean fclean re
