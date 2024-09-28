# Directories
SRC_DIR      := ./src
OBJ_DIR      := ./obj
INCLUDES_DIR := ./includes
LIBFT_DIR    := ./libft
LIBFT        := $(LIBFT_DIR)/libft.a

# Minilibx
MLX_PATH	:= mlx/
MLX_NAME	:= libmlx.a
MLX			:= $(MLX_PATH)$(MLX_NAME)

# Compiler and flags
CFLAGS = -O3 -Wall -Wextra -Werror
LEAKCHECK = -g #-fsanitize=address
CC = cc $(CFLAGS) $(LEAKCHECK)
LFLAGS = -L./mlx -lmlx -L./libft -lft -lXext -lX11 -lm $(LEAKCHECK)
IFLAGS   := -I$(LIBFT_DIR) -I$(INCLUDES_DIR)

RM    := rm -f
NORM  := norminette

# Name of the executable
NAME := cub3D

# Includes files
INCLUDES_FILES := cub3D.h
INCLUDES       := $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# Srcs
SRC_FILES := main.c \
			minimap/minimap.c \
			minimap/fov.c \
			minimap/draw_line.c \
			minimap/map_utils.c \
			raycasting/angle_utils.c \
			raycasting/intersection_utils.c \
			raycasting/intersection.c \
			raycasting/raycasting.c \
			rendering/drawing_utils.c \
			rendering/pixel_utils.c \
			rendering/rendering.c \
			free_and_exit.c \
			help.c \
			hooks.c \
			initialization.c \
			player.c \
			validation.c \
			input_file.c \
			check_scene.c \
			map_elem_checks.c \
			load_texture.c \
			test_utils.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_FILES := $(SRC_FILES:.c=.o)
OBJ       := $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Compilation rules
$(NAME): $(LIBFT) $(OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(IFLAGS) $(LFLAGS) $(MLX)

all: $(NAME)
	@echo "\033[0;32m"
	@echo '>>============================================================<<'
	@echo '||                                                            ||'
	@echo '||  ________   ___  ___   ________   ________   ________      ||'
	@echo '|| |\   ____\ |\  \|\  \ |\   __  \ |\_____  \ |\   ___ \     ||'
	@echo '|| \ \  \___| \ \  \\\  \\ \  \|\ /_\|____|\ /_\ \  \_|\ \    ||'
	@echo '||  \ \  \     \ \  \\\  \\ \   __  \     \|\  \\ \  \ \\ \   ||'
	@echo '||   \ \  \____ \ \  \\\  \\ \  \|\  \   __\_\  \\ \  \_\\ \  ||'
	@echo '||    \ \_______\\ \_______\\ \_______\ |\_______\\ \_______\ ||'
	@echo '||     \|_______| \|_______| \|_______| \|_______| \|_______| ||'
	@echo '||                                                            ||'
	@echo '>>============================================================<<'
	@echo "\033[0m"
bonus: all

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

.PHONY: all bonus

# Cleanup rules
clean:
	@make -C $(LIBFT_DIR) clean --no-print-directory
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re

ASCII_ART := $(call ASCII_ART)

# Norminette
norm:
	@$(NORM) $(SRC_DIR)/*.c $(INCLUDES_DIR)/*.h

.PHONY: norm

# Custom commands
leaks: $(NAME)
	valgrind -s --leak-check=full --show-reachable=yes \
	--show-leak-kinds=all --trace-children=yes --track-fds=yes \
	--track-origins=yes \
	./cub3D

.PHONY: leaks
