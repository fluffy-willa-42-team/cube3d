/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:33:07 by awillems          #+#    #+#             */
/*   Updated: 2022/11/01 11:28:43 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include "MLX42/MLX42.h"
# include <stdint.h>
# include <stddef.h>

# include "cube_types.h"

/* ************************************************************************** */

# define PI    3.14159265359
# define PI1_2 1.57079632679
# define PI3_2 4.71238898038
# define PI2   6.28318530718
# define MINIMAP_SIZE 32

# define WIN_WIDTH 1000
# define WIN_HEIGHT 600

/* ************************************************************************** */

typedef struct s_texture {
	int		type;
	char	*path;
	void	*image;
	int		color;
}	t_texture;


/* ************************************************************************** */

typedef struct s_chunk {
	int32_t		type;
	t_coord_i32	coord;
	t_texture	north;
	t_texture	east;
	t_texture	west;
	t_texture	south;
	t_texture	ceiling;
	t_texture	floor;
}	t_chunk;

typedef struct s_entity {
	int32_t		type;
	t_coord_f64	coord;
	int 		nb_texture;
	t_texture	*texture;
}	t_entity;

/* ************************************************************************** */

typedef struct s_map {
	int32_t array[8][8];
	int32_t height;
	int32_t width;
}	t_map;

typedef struct s_mlx_param {
	mlx_t 		*mlx;
	mlx_image_t *img;
	int32_t 	height;
	int32_t 	width;
}	t_mlx_param;

typedef struct s_player {
	t_coord_f64 coord;
	double		alpha;
	t_coord_f64 delta;
}	t_player;

typedef struct s_game {
	t_mlx_param param;
	t_map 		map;
	t_player	player;
}	t_game;


/* ************************************************************************** */

#endif /* CUBE3D_H */