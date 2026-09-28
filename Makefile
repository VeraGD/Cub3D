NAME		= cub3D
BONUS_NAME	= cub3D_bonus
CFLAGS		= -Wextra -Wall -Werror -g
LIBMLX		= ./lib/MLX42
CC			= gcc

HEADERS		= -I $(LIBMLX)/include #-I ./include/so_long.h
LIBFT_DIR	= ./lib/libft 
MLX_PATH	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
LIBFT_PATH	= ./lib/libft/libft.a
LIBS_PATH	= $(LIBFT_PATH) $(MLX_PATH)
SRCS			= ./src/cub3d.c \
					./src/validation.c \
					./src/initialize.c \
					./src/texture_parsing_gf.c \
					./src/number_parsing.c \
					./src/utils_parseo.c \
					./src/ft_split_double.c \
					./src/free_functions.c \
					./src/error_functions.c \
					./src/map_error.c \
					./src/map_parsing.c \
					./src/raycaster.c \
					./src/hooks.c \
					./src/drawing_frame.c \
					./src/raycaster_utils.c \
					./src/player.c \

SRCS_BONUS			= ./src_bonus/cub3d_bonus.c \
					./src_bonus/validation_bonus.c \
					./src_bonus/initialize_bonus.c \
					./src_bonus/texture_parsing_gf_bonus.c \
					./src_bonus/number_parsing_bonus.c \
					./src_bonus/utils_parseo_bonus.c \
					./src_bonus/ft_split_double_bonus.c \
					./src_bonus/free_functions_bonus.c \
					./src_bonus/error_functions_bonus.c \
					./src_bonus/map_error_bonus.c \
					./src_bonus/map_parsing_bonus.c \
					./src_bonus/raycaster_bonus.c \
					./src_bonus/hooks_bonus.c \
					./src_bonus/drawing_frame_bonus.c \
					./src_bonus/raycaster_utils_bonus.c \
					./src_bonus/player_bonus.c \
					./src_bonus/minimap_bonus.c 

OBJ_DIR		= ./obj
OBJ_BONUS_DIR	= ./obj_bonus

OBJS		= ${SRCS:./src/%.c=$(OBJ_DIR)/%.o}
OBJS_BONUS		= ${SRCS_BONUS:./src_bonus/%.c=$(OBJ_BONUS_DIR)/%.o}

GREEN		= \033[1;32m

GIT_MLX 	= git clone https://github.com/42-Fundacion-Telefonica/MLX42.git $(LIBMLX)

all: check_mlx $(NAME)

bonus: check_mlx $(BONUS_NAME)

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(OBJ_BONUS_DIR)/%.o: ./src_bonus/%.c
	@mkdir -p $(OBJ_BONUS_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@echo "wait..."
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(OBJS) $(LIBS_PATH) $(HEADERS) -I ./include/cub3d.h -o $(NAME)
	@echo "${GREEN}type: ./cub3D maps/map1.cub"

$(BONUS_NAME): $(OBJS_BONUS)
	@echo "wait..."
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(OBJS_BONUS) $(LIBS_PATH) $(HEADERS) -I ./include/cub3d_bonus.h -o $(BONUS_NAME)
	@echo "${GREEN}type: ./cub3D_bonus maps/map1.cub"

clean:
	@rm -rf $(OBJ_DIR) $(OBJS_BONUS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -rf $(NAME) $(BONUS_NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

check_mlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "MLX42 not found. Downloading..."; \
		make download_mlx; \
	fi

download_mlx:
		$(GIT_MLX)
		cd $(LIBMLX) && cmake -B build
		cd $(LIBMLX) && cmake --build build -j4
		clear

undownload_mlx:
		rm -rf $(LIBMLX)

.PHONY: all, clean, fclean, re, libmlx