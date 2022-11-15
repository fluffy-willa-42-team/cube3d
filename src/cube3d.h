/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:33:07 by awillems          #+#    #+#             */
/*   Updated: 2022/11/15 12:04:04 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include "MLX42/MLX42.h"
# include <stdint.h>
# include <stddef.h>

# include "cube_types.h"

/* #####=====----------			Common Math Var			 ----------=====##### */

# define PI    3.14159265359
# define PI1_6 0.52359877559
# define PI1_3 1.0471975512
# define PI1_2 1.57079632679
# define PI3_2 4.71238898038
# define PI2   6.28318530718

/* #####=====----------			Mlx Config Var			 ----------=====##### */

# define WIN_WIDTH	800
# define WIN_HEIGHT	800

/* #####=====----------		Ray Caster Config Var		 ----------=====##### */

# define FOV_ANGLE				PI / 3

/* ************************************************************************** */

typedef enum s_texture_type {
	UNDEFINED	= 0b000,
	VALID		= 0b001,
	COLOR		= 0b000,
	IMAGE		= 0b010,
	SKYBOX		= 0b100,
}	t_texture_type;

typedef struct s_texture {
	t_texture_type	type;
	mlx_texture_t	*image;
	int				color;
}	t_texture;

/* ************************************************************************** */

typedef struct s_chunk {
	int32_t		type;
	t_coord_i32	coord;
	t_texture	*north;
	t_texture	*south;
	t_texture	*east;
	t_texture	*west;
	t_texture	*ceiling;
	t_texture	*floor;
}	t_chunk;

typedef struct s_entity {
	int32_t		type;
	t_coord_f64	coord;
	int 		nb_texture;
	t_texture	*texture;
}	t_entity;

/* ************************************************************************** */

typedef struct s_map {
	int32_t array[20][20];
	uint32_t height;
	uint32_t width;
}	t_map;

typedef struct s_mlx_param {
	mlx_t 		*mlx;
	mlx_image_t *img;
	double		hob_mult;
	int32_t		minimap_size;
	int32_t 	height;
	int32_t 	width;
}	t_mlx_param;

typedef struct s_player {
	t_coord_f64 coord;
	double		z;
	double		alpha;
	t_coord_f64 cosin;
}	t_player;

typedef struct s_game {
	t_mlx_param param;
	t_map 		map;
	t_player	player;
	t_texture	skybox;
	t_texture	temp;
	t_texture	temp1;
	t_texture	temp2;
	t_chunk		chunk0;
	t_chunk		chunk1;
	t_chunk		chunk2;
	t_chunk		chunk3;
	t_chunk		chunk4;
}	t_game;


/* ************************************************************************** */

#endif /* CUBE3D_H */