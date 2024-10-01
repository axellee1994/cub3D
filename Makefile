# Directories
SRC_DIR      := ./src
MANDATORY_DIR := $(SRC_DIR)/mandatory
BONUS_DIR    := $(SRC_DIR)/bonus
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

# Name of the executables
NAME := cub3D
BONUS_NAME := cub3D_bonus

# Includes files
INCLUDES_FILES := cub3D.h
INCLUDES       := $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# Srcs for normal build
MANDATORY_SRC_FILES := main.c \
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
			loading/input_file.c \
			loading/scene_loading.c \
			loading/loading_utils.c \
			loading/check_scene.c \
			loading/process_map.c \
			init_texture.c

# Srcs for bonus build
BONUS_SRC_FILES := main_bonus.c \
			minimap/minimap_bonus.c \
			minimap/map_utils_bonus.c \
			minimap/draw_line_bonus.c \
			raycasting/angle_utils_bonus.c \
			raycasting/intersection_utils_bonus.c \
			raycasting/intersection_bonus.c \
			raycasting/raycasting_bonus.c \
			rendering/drawing_utils_bonus.c \
			rendering/pixel_utils_bonus.c \
			rendering/rendering_bonus.c \
			free_and_exit_bonus.c \
			help_bonus.c \
			hooks_bonus.c \
			initialization_bonus.c \
			player_bonus.c \
			loading/input_file_bonus.c \
			loading/scene_loading_bonus.c \
			loading/loading_utils_bonus.c \
			loading/check_scene_bonus.c \
			loading/process_map_bonus.c \
			init_texture_bonus.c \

MANDATORY_SRC := $(addprefix $(MANDATORY_DIR)/, $(MANDATORY_SRC_FILES))
BONUS_SRC := $(addprefix $(BONUS_DIR)/, $(BONUS_SRC_FILES))

MANDATORY_OBJ_FILES := $(MANDATORY_SRC_FILES:.c=.o)
BONUS_OBJ_FILES := $(BONUS_SRC_FILES:.c=.o)

MANDATORY_OBJ := $(addprefix $(OBJ_DIR)/, $(MANDATORY_OBJ_FILES))
BONUS_OBJ := $(addprefix $(OBJ_DIR)/, $(BONUS_OBJ_FILES))

# Compilation rules
$(NAME): $(LIBFT) $(MANDATORY_OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(MANDATORY_OBJ) $(IFLAGS) $(LFLAGS) $(MLX)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJ) $(IFLAGS) $(LFLAGS) $(MLX)

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

bonus: $(BONUS_NAME)
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
	@echo '||                         BONUS                              ||'
	@echo '||                                                            ||'
	@echo '>>============================================================<<'
	@echo "\033[0m"

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

.PHONY: all bonus

# Cleanup rules
clean:
	@make -C $(LIBFT_DIR) clean --no-print-directory
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

re_bonus: fclean bonus

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

.PHONY: all bonus clean fclean re re_bonus