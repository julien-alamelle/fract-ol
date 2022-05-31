# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalamell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 13:18:09 by jalamell          #+#    #+#              #
#    Updated: 2022/05/31 18:52:53 by jalamell         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -I $(INCL_DIR)

SRC_DIR=src
OBJ_DIR=.obj
INCL_DIR=incl

FILES=main hsl_to_rgb data fractal cpx input hook
FILES_EX=main_extra data_extra fractal_extra cpx input_extra hook
HEADER=fractol
HEADER_EX=$(addsuffix _extra,$(HEADER))

SRC=$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(FILES)))
OBJ=$(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(FILES)))
HEAD=$(addprefix $(INCL_DIR)/,$(addsuffix .h,$(HEADER)))
SRC_EX=$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(FILES_EX)))
OBJ_EX=$(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(FILES_EX)))
HEAD_EX=$(addprefix $(INCL_DIR)/,$(addsuffix .h,$(HEADER_EX)))
NAME=fractol
EXTRA=fractol_extra
ALL=$(NAME) $(EXTRA)

FRAMEWORK=-framework OpenGL -framework AppKit
FRAMEWORK_EX=$(FRAMEWORK) -framework OpenCL
MLX_DIR=minilibx
MLX_FILES=mlx_init_loop.m mlx_int_str_to_wordtab.c mlx_mouse.m mlx_new_image.m mlx_new_window.m mlx_png.c mlx_shaders.c mlx_xpm.c
MLX=$(addprefix $(MLX_DIR)/, libmlx.a)
MLX_DPC=$(addprefix $(MLX_DIR)/, $(MLX_FILES))
all: $(ALL)

clean:
	rm -Rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(ALL)

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile $(HEAD)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(MLX_DIR) -o $@ -c $<

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L $(MLX_DIR) -l mlx $(FRAMEWORK) -lm -o $@

$(EXTRA): $(MLX) $(OBJ_EX)
	$(CC) $(CFLAGS) $(OBJ_EX) -L $(MLX_DIR) -l mlx $(FRAMEWORK_EX) -lm -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MLX): $(MLX_DPC)
	@make -C $(MLX_DIR) 

.PHONY: all clean fclean re
