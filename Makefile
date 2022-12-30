# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 10:47:56 by awillems          #+#    #+#              #
#    Updated: 2022/12/20 15:07:48 by mahadad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                  CONFIG
# **************************************************************************** #

NAME		= cub3D

# **************************************************************************** #

SRCS		=	 \
read_file.c \
file_sani.c \
open_file.c \
check_x.c \
check_map_utils.c \
check_map.c \
check_y.c \
zero_conv.c \
space_conv.c \
player_conv.c \
one_conv.c \
file_conv.c \
cub_map_conv.c \
tex_conv_utils.c \
cub_tex_conv.c \
get_chunk.c \
store_entity.c \
check_chunk.c \
get_next_chunk.c \
get_line_width.c \
set_map_size.c \
store_map.c \
get_map_char_ptr.c \
set_color_texture.c \
init_texture.c \
set_tex_config_utils.c \
set_tex_config.c \
get_current_tex_config.c \
load_texture_config.c \
cube_to_t_map.c \
find_tex_type.c \
get_tex.c \
authzed_cube_char.c \
authzed_cube_tex.c \
parser.c \
main.c \
get_wall.c \
draw_wall.c \
draw_floor.c \
draw_transparency.c \
draw_wall_text.c \
ray_caster.c \
draw_skybox.c \
minimap.c \
minimap_utils.c \
get_intersect.c \
get_distance.c \
get_inter_init.c \
get_inter_step.c \
hooks_utils.c \
player_management.c \
minimap_management.c \
map_management.c \
save_hooks.c \
use_hooks.c \
player_move.c \
coordinate.c \
init_player.c \
init_params.c \
print_err.c \
math_utils.c \
destroy_data.c \
destroy_t_parser.c \
struct_set.c \
mlx_extra.c \
draw_elem.c \
draw_image.c \
draw_minimap.c \
run_game.c


#SRCS		= $(SRCS_FIND)

# **************************************************************************** #

SRC_DIR		= src
INC_DIR		= include
OBJ_DIR 	= $(NAME)_obj
LIB_DIR		= lib
# **************************************************************************** #

CC			= gcc
OBJ_EXT		= .o
CODE_EXT	= .c
HEAD_EXT	= .h
INC			= -I include -Ilib/vector-lib/include -Ilib/libft/include
FLAGS		= -Wall -Wextra -Werror

# **************************************************************************** #
#                                  PARAMS
# **************************************************************************** #

COLOR_NORMAL= \033[32;0m
COLOR_RED	= \033[31;1m
COLOR_BLUE	= \033[36;1m
COLOR_GREEN	= \033[32;1m

# **************************************************************************** #

DEBUG		= 0
TEST_UNIT	= 0
SANI		= 0
WRA			= 0

ifeq ($(TEST_UNIT), 1)
	SANI = 1
	FLAGS += -D CUBE3D_UNITEST_PARSER=1
	MAKE_FLAG += TEST_UNIT=1
endif

ifeq ($(SANI), 1)
	FLAGS += -fsanitize=address
	DEBUG = 1
	MAKE_FLAG += SANI=1
endif

ifeq ($(DEBUG), 1)
	FLAGS += -g3
	FLAGS += -D DEBUG_PRINT=1
	FLAGS += -D DEBUG_PARSE=1
	MAKE_FLAG += DEBUG=1
endif

ifeq ($(shell uname),Darwin)
	FLAGS_COMP	= -lmlx -framework OpenGL -framework AppKit 
	INC 		+= -I$(shell brew --prefix glfw)/include
	FLAGS_COMP	+= -lglfw -L $(shell brew --prefix glfw)/lib
	ALL_LIB 	+=	\
					lib/libft \
					lib/minilibx_opengl_20191021 \
					lib/vector-lib
endif

ifeq ($(shell uname),Linux)
	FLAGS += -D KEY_X11=1
	FLAGS_COMP	= -ldl -lglfw -pthread -lm -lX11 -lXext  -I lib/minilibx-linux -D KEY_X11=1
	INC			+= -I lib/minilibx-linux
	ALL_LIB 	+=	\
					lib/libft \
					lib/vector-lib \
					lib/minilibx-linux
endif

# **************************************************************************** #

VPATH		= $(shell find $(SRC_DIR)/ -type d)

# Finds all sources in the SRC_DIR
SRCS_FIND	= $(notdir $(shell find $(SRC_DIR) -type f -name "*$(CODE_EXT)"))

# Compiles all SRCS into .o files in the OBJ_DIR
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRCS:$(CODE_EXT)=$(OBJ_EXT)))

# Finds all folders in the LIB_DIR
# ALL_LIB		= $(shell find $(LIB_DIR)/ -maxdepth 1 -mindepth 1 -type d)

# Finds all the compiled libraries in ALL_LIB
LIB			= $(shell find $(LIB_DIR) -type f -name "*.a")

# Finds all headers in the SRC_DIR and creates links to the original header files
HEADER		= $(addprefix $(INC_DIR)/, $(notdir $(shell find $(SRC_DIR)/ -type f -name "*$(HEAD_EXT)")))

# All directories
DIR			= $(SRC_DIR) $(INC_DIR) $(OBJ_DIR) $(LIB_DIR)

# Path to here
THISPATH	= $(shell pwd)

# **************************************************************************** #
#                                 RULES
# **************************************************************************** #

all: $(DIR) lib_comp $(NAME)

# Creates every repositories if it does not exist
$(DIR):
	@mkdir $@

# Compiles every lib in the lib repository
lib_comp:
	@for path in $(ALL_LIB); do \
		if [ -f $$path/Makefile ]; then \
			make -sC $$path $(MAKE_FLAG) all;\
		fi; \
	done

# Takes any C/CPP files and transforms into an object into the OBJ_DIR
$(OBJ_DIR)/%$(OBJ_EXT): %$(CODE_EXT) $(HEADER)
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<
	@printf "$(COLOR_RED).$(COLOR_NORMAL)"

# Takes any header files and creates a hard link in INC_DIR
$(INC_DIR)/%$(HEAD_EXT): %$(HEAD_EXT)
	@ln -s $(THISPATH)/$< $(INC_DIR)
	@printf "$(COLOR_BLUE).$(COLOR_NORMAL)"

# Takes an name of executable and compiles everything into it
$(NAME): print $(HEADER) $(OBJ)
	@$(CC) $(FLAGS) $(INC) $(OBJ) $(LIB) $(FLAGS_COMP) -o $(NAME)
	@chmod 777 $(NAME)
	@printf "\n"
	@if [ $(DEBUG) = 2 ]; then printf "$(COLOR_RED)/!\ DEBUG ENABLE /!\ $(COLOR_NORMAL)\nFlag used:\n"; printf "    %s\n" $(FLAGS);fi

print:
	@if [ $(DEBUG) = 1 ]; then printf "$(COLOR_RED)/!\ Debug ➜  $(COLOR_NORMAL)"; fi
	@printf "$(COLOR_GREEN)$(NAME) : $(COLOR_NORMAL)"

# **************************************************************************** #

clean:
	@rm -rf $(OBJ)
	@for path in $(ALL_LIB); do \
	if [ -f $$path/Makefile ]; then \
		make -sC $$path clean;\
	fi; \
done

# **************************************************************************** #

fclean:
	@rm -rf $(OBJ) $(INC_DIR)* $(NAME)
	@for path in $(ALL_LIB); do \
	if [ -f $$path/Makefile ]; then \
		make -sC $$path fclean;\
	fi; \
done

# **************************************************************************** #

print_src:
	@for elem in $(SRCS_FIND); do \
		echo $$elem;\
	done

# **************************************************************************** #

re: fclean all

.PHONY: all, fclean, clean, re, print_src, $(ALL_LIB), exe, fluffy