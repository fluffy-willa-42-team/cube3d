/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:33:07 by awillems          #+#    #+#             */
/*   Updated: 2022/10/25 13:39:28 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include "MLX42/MLX42.h"
# include <stdint.h>
# include <stddef.h>

/* ************************************************************************** */

# define MINIMAP_SIZE 64

#  define WIN_WIDTH 500
#  define WIN_HEIGHT 500

/* ************************************************************************** */

typedef struct s_texture {
	int		type;
	char	*path;
	void	*image;
	int		color;
}	t_texture;

typedef struct s_coord_i32 {
	int32_t x;
	int32_t y;
}	t_coord_i32;

typedef struct s_coord_f64 {
	double x;
	double y;
}	t_coord_f64;

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
	int32_t heigth;
	int32_t width;
}	t_map;

typedef struct s_mlx_param {
	mlx_t 		*mlx;
	mlx_image_t *img;
	int32_t 	height;
	int32_t 	width;
}	t_mlx_param;

typedef struct s_game {
	t_mlx_param param;
	t_map 		map;
}	t_game;

/* ************************************************************************** */

#endif /* CUBE3D_H */