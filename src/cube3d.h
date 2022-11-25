/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:33:07 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 12:55:24 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdint.h>
# include <stddef.h>
# include "vector_lib.h"

/* ************************************************************************** */

/**
 * @param UNDEFINED
 * @param VALID
 * @param COLOR
 * @param IMAGE
 * @param SKYBOX
 * @param ALLOW_CLIP
 * @param TRANSPARENCY
 */
typedef enum e_texture_type {
	UNDEFINED		= 0b0000001,
	VALID			= 0b0000010,
	COLOR			= 0b0000100,
	IMAGE			= 0b0001000,
	SKYBOX			= 0b0010000,
	ALLOW_CLIP		= 0b0100000,
	TRANSPARENCY	= 0b1000000
}	t_texture_type;

/**
 * @param type           (t_texture_type)
 * @param token          (char)
 * @param sky_box_token  (char)
 * @param path           (char*)
 * @param image          (void*)
 * @param color          (unit32_t)
 */
typedef struct s_texture {
	t_texture_type			type;
	char					token;
	char					sky_box_token;
	char					*path;
	void					*image;
	uint32_t				color;
	struct s_texture		*skybox_tex;
}	t_texture;

typedef struct s_coord_f64 {
	double	x;
	double	y;
}	t_coord_f64;

typedef struct s_coord_i32 {
	int32_t	x;
	int32_t	y;
	int32_t	z;
}	t_coord_i32;

typedef struct s_coord_f32 {
	double	x;
	double	y;
	double	z;
}	t_coord_f32;

/* ************************************************************************** */

/**
 *     TOP    | NORTH | ENTITY
 *     -------0-------0-------
 *     WEST   | EAST  | TEX
 *     -------0-------0-------
 *     BOTTOM | SOUTH | OPT
 */

typedef struct s_entity {
	int32_t		type;
	t_coord_f64	coord;
	int			nb_texture;
	t_texture	*texture;
}	t_entity;

/**
 * @param WHITE_SPACE_CHUNK For the white space chunk, so no data
 * @param GOOD_CHUNK        For the chunk with data
 * @param BAD_CHUNK         For the chunk that have white space and data
 */
typedef enum e_chunk_type {
	WHITE_SPACE_CHUNK,
	GOOD_CHUNK,
	BAD_CHUNK
}				t_chunk_type;

/**
 * @param type     (int32_t)
 * @param coord    (t_coord_i32)
 * @param north    (t_texture *)
 * @param east     (t_texture *)
 * @param west     (t_texture *)
 * @param south    (t_texture *)
 * @param ceiling  (t_texture *)
 * @param floor    (t_texture *)
 * @param skybox   (t_texture *)
 */
typedef struct s_chunk {
	int32_t		type;
	t_coord_i32	coord;
	t_texture	*north;
	t_texture	*east;
	t_texture	*west;
	t_texture	*south;
	t_texture	*ceiling;
	t_texture	*floor;
	t_texture	*skybox;
}	t_chunk;

# define E_EMPTY '.'

/**
 * Player macro
 */

# define E_PLAYER			'P'
# define OPT_P_NORTH		'N'
# define OPT_P_SOUTH		'S'
# define OPT_P_EAST			'E'
# define OPT_P_WEST			'W'

/**
 * Enemy macro
 */
# define E_ENEMY			'E'
# define T_ENEMY_DEFAULT	'./TODO'
# define OPT_E_DEFAULT	'.'

/**
 * Collectible macro
 */
# define E_COLLECTIBLE	'C'
# define OPT_C_AMMO		'A'
# define OPT_C_HEALTH	'H'

/**
 * Door macro
 */
# define E_DOOR			'D'
# define OPT_D_N			'N'
# define OPT_D_E			'E'

/**
 * Furniture macro
 */
# define E_FURNITURE		'F'

typedef struct s_map
{
	int32_t		height;
	int32_t		width;
	t_coord_i32	size;
	t_vec		tex_list;
	t_vec		map;
}				t_map;

/* ************************************************************************** */

#endif /* CUBE3D_H */