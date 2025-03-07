# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 12:21:50 by hitran            #+#    #+#              #
#    Updated: 2025/03/04 14:27:31 by hitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC 				= cc
CFLAGS 			= -g -Wall -Wextra -Werror
MLX42_FLAGS		= -ldl -lglfw -pthread -lm
INCLUDES 		= -I./includes -I./libs/libft -I./libs/MLX42/include/MLX42
RM 				= rm -rf

# Directories
SRC_DIR 			= srcs
LIB_DIR 			= libs
OBJ_DIR				= obj
LIB_DIR 			= libs
LIBFT_DIR	 		= $(LIB_DIR)/libft
MLX42_DIR			= $(LIB_DIR)/MLX42
CUB3D_DIR			= $(SRC_DIR)/cub3d
EVENT_DIR			= $(SRC_DIR)/event
MAP_DIR				= $(SRC_DIR)/map
UTILS_DIR			= $(SRC_DIR)/utility
ASSET_MANAGER_DIR	= $(SRC_DIR)/asset_manager
RAY_DIR				= $(SRC_DIR)/ray_casting


# Source files by directory
CUB3D_FILES			=	init.c free.c exit.c display.c utils.c \
						init_rays.c

EVENT_FILES			=	event_loop_handler.c \
						event_close_handler.c \
						draw_map.c \
						draw_minimap.c \
						draw_player.c \
						draw_scene.c \
						collision.c \
						key_inputs.c \
						mouse_inputs.c \
						inputs.c \
						animate.c

UTIL_FILES			=	ft_error.c \
						ft_validate_path.c ft_is_valid_pos.c\
						ft_max.c \
						ft_readline.c ft_is_all_white_spaces.c ft_array_len.c ft_clean_array.c \
						ft_convert_color.c ft_set_color.c ft_fill_color.c \
						ft_get_pixels.c ft_copy_pixels.c ft_del_pixels.c\
						ft_destroy_imgs.c
						
MAP_FILES			=	read_element.c read_grid.c read_map.c \
						validate_grid.c is_enclosed.c utils.c \
						validate_png.c

 
ASSET_MANAGER_FILES	=	am_load_png.c am_load_png_ray.c am_load_sprite.c \
						am_init.c am_free.c

RAY_FILES			=	ray_casting.c find_hit_point.c process_ray_hit.c 

SRC_FILES			= 	./srcs/main.c \
						$(addprefix $(CUB3D_DIR)/, $(CUB3D_FILES)) \
						$(addprefix $(EVENT_DIR)/, $(EVENT_FILES)) \
						$(addprefix $(UTILS_DIR)/, $(UTIL_FILES)) \
						$(addprefix $(ASSET_MANAGER_DIR)/, $(ASSET_MANAGER_FILES)) \
						$(addprefix $(MAP_DIR)/, $(MAP_FILES)) \
						$(addprefix $(RAY_DIR)/, $(RAY_FILES)) 

# Library
LIBFT 				= $(LIBFT_DIR)/libft.a
MLX42				= $(MLX42_DIR)/build/libmlx42.a

# Executables
NAME 				= cub3D
NAME_BONUS			= cub3D_bonus


# Targets
all : mandatory

mandatory : .mandatory
.mandatory: $(LIBFT) $(MLX42) $(SRC_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_FILES) $(LIBFT) $(MLX42) $(MLX42_FLAGS) -o $(NAME)
	@touch .mandatory

bonus: .bonus
.bonus: $(LIBFT) $(MLX42) $(SRC_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_FILES) $(LIBFT) $(MLX42) $(MLX42_FLAGS) -o $(NAME_BONUS)
	@touch .bonus

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX42): .mlx42
.mlx42: 
	@$(RM) $(MLX42_DIR)
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR)
	@cd $(MLX42_DIR) && mkdir -p build && cd build && cmake .. && cmake --build . -j4
	@cd ..
	@$(RM) $(MLX42_DIR)/.git
	@touch .mlx42

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME) $(NAME_BONUS) $(MLX42_DIR) .bonus .mandatory .mlx42
	
re: fclean all

.PHONY: all clean fclean re mandatory bonus