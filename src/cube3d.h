/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:33:07 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 11:15:25 by awillems         ###   ########.fr       */
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
# define PI1_2 1.57079632679
# define PI1_3 1.0471975512
# define PI1_4 0.78539816339
# define PI1_6 0.52359877559
# define PI3_2 4.71238898038
# define PI2   6.28318530718

/* #####=====----------			Mlx Config Var			 ----------=====##### */

# define WIN_WIDTH	800
# define WIN_HEIGHT	800

# define ANGLE_START	PI

/* #####=====----------		Ray Caster Config Var		 ----------=====##### */

// FOV = PI / 3
# define FOV_ANGLE			1.0471975512
# define HEIGTH_OF_BLOCK	WIN_HEIGHT / 10

# define MIDDLE_OF_SCREEN	WIN_HEIGHT / 2
# define FOV_INCRE			(double) (FOV_ANGLE) / WIN_WIDTH
# define FOV_ANG_1_2		(double) (FOV_ANGLE) / 2

/* ************************************************************************** */

typedef enum e_texture_type {
	UNDEFINED		= 0b00000,
	VALID			= 0b00001,
	IMAGE			= 0b00010,
    SKYBOX			= 0b00100,
    ALLOW_CLIP		= 0b01000,
    TRANSPARENCY	= 0b10000
}    t_texture_type;

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

typedef struct s_wall_inter
{
	t_chunk		*chunk1;
	t_chunk		*chunk2;
	t_texture	*text1;
	t_texture	*text2;
}	t_wall_inter;


/* ************************************************************************** */

typedef struct s_map {
	char	 	array[23][20];
	t_chunk		*map;
	uint32_t	height;
	uint32_t	width;
}	t_map;

typedef struct s_mlx_param {
	mlx_t 		*mlx;
	mlx_image_t *img;
	double		hob_mult;
	int32_t		minimap_size;
	double		minimap_point_size;
	int32_t 	height;
	int32_t 	width;
}	t_mlx_param;

typedef struct s_player {
	t_coord_f64 pos;
	double		alpha;
	t_coord_f64 cosin;
}	t_player;

typedef struct s_game {
	t_mlx_param 	param;
	t_map 			map;
	t_player		player;
	t_texture		skybox;
	t_texture		temp;
	t_texture		temp1;
	t_texture		temp2;
	t_texture		t_cont1;
	t_texture		t_cont2;
	t_texture		t_cont3;
	t_texture		t_cont4;
	t_texture		t_cont5;
	t_texture		temp3;
	t_texture		clip;
	t_chunk			chunk0;
	t_chunk			chunk1;
	t_chunk			chunk2;
	t_chunk			chunk3;
	t_chunk			chunk4;
	t_chunk			chunk5;
	t_chunk			cont1;
	t_chunk			cont2;
	t_chunk			cont3;
	t_chunk			cont4;
	t_chunk			chunk6;
	t_chunk			chunk7;
}	t_game;


/* ************************************************************************** */

#endif /* CUBE3D_H */