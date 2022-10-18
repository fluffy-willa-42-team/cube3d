# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awillems <awillems@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 10:47:56 by awillems          #+#    #+#              #
#    Updated: 2022/10/10 10:56:39 by awillems         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                  CONFIG
# **************************************************************************** #

NAME		= cube3d

# **************************************************************************** #

# SRCS		=	

SRCS		= $(SRCS_FIND)

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
INC			= -I include -I lib/MLX42/include/ -I lib/MLX42/
FLAGS		= -Wall -Wextra -Werror
FLAGS_COMP	= -lglfw -L "/Users/awillems/.brew/opt/glfw/lib/"

# **************************************************************************** #
#                                  PARAMS
# **************************************************************************** #

COLOR_NORMAL= \033[32;0m
COLOR_RED	= \033[31;1m
COLOR_BLUE	= \033[36;1m
COLOR_GREEN	= \033[32;1m

# **************************************************************************** #

DEBUG		= 0
SANI		= 0
WRA			= 0

ifeq ($(SANI), 1)
	FLAGS += -fsanitize=address
	DEBUG = 1
	MAKE_FLAG += SANI=1
endif

ifeq ($(DEBUG), 1)
	FLAGS += -g3
	FLAGS += -D DEBUG_PRINT=1
	MAKE_FLAG += DEBUG=1
endif

# **************************************************************************** #

VPATH		= $(shell find $(SRC_DIR)/ -type d)

# Finds all sources in the SRC_DIR
SRCS_FIND	= $(notdir $(shell find $(SRC_DIR) -type f -name "*$(CODE_EXT)"))

# Compiles all SRCS into .o files in the OBJ_DIR
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRCS:$(CODE_EXT)=$(OBJ_EXT)))

# Finds all folders in the LIB_DIR
ALL_LIB		= $(shell find $(LIB_DIR)/ -maxdepth 1 -mindepth 1 -type d)

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
# @for path in $(ALL_LIB); do \
# 	if [ -f $$path/Makefile ]; then \
# 		make -sC $$path clean;\
# 	fi; \
# done

# **************************************************************************** #

fclean:
	@rm -rf $(OBJ) $(INC_DIR)* $(NAME)
# @for path in $(ALL_LIB); do \
# 	if [ -f $$path/Makefile ]; then \
# 		make -sC $$path fclean;\
# 	fi; \
# done

# **************************************************************************** #

print_src:
	@for elem in $(SRCS_FIND); do \
		printf "[%s]\n" $$path;\
		echo $$elem;\
	done

# **************************************************************************** #

re: fclean all

# **************************************************************************** #

exe: all
	@bash -c "./$(NAME)"

# **************************************************************************** #

fluffy:
	git config user.name "matthew-dreemurr"
	git config user.email "hadadmat@gmail.com"


.PHONY: all, fclean, clean, re, print_src, $(ALL_LIB), exe, fluffy