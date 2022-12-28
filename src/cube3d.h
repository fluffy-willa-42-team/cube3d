/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:33:07 by awillems          #+#    #+#             */
/*   Updated: 2022/12/28 15:28:23 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdint.h>
# include <stddef.h>
# include "vector_lib.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
# include <stdlib.h>

# include "mlx.h"
# include "cube_types.h"
# include "hooks.h"

# ifndef DEBUG_PARSE
#  define DEBUG_PARSE 0
# endif /*DEBUG_PARSE*/

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
# define PLAYER_RADIUS	(double) 0.03
# define PLAYER_SPEED	(double) 0.03

/* #####=====----------		Ray Caster Config Var		 ----------=====##### */

// FOV = PI / 3
# define FOV_ANGLE			1.0471975512

/* ************************************************************************** */

typedef struct s_image
{
	uint32_t	width;
	uint32_t	height;
	uint32_t	*buffer;
}	t_image;

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
 * @param token_ptr  (char)
 * @param path           (char*)
 * @param image          (mlx_tex*)
 * @param color          (unit32_t)
 */
typedef struct s_texture {
	t_texture_type			type;
	char					token;
	char					token_ptr;
	char					*path;
	t_image					*image;
	uint32_t				color;
	struct s_texture		*skybox_tex;
}	t_texture;

/* ************************************************************************** */

typedef struct s_param {
	void		*mlx;
	void		*win;
	t_image		*img;
	double		hob_mult;
	uint32_t	minimap_size;
	double		player_size;
	uint32_t	max_minimap_size;
	double		speed;
	int			has_ended;
	double		ray;
}	t_param;

typedef struct s_player {
	t_coord_f64	pos;
	double		alpha;
	t_coord_f64	cosin;
	int			exist;
}	t_player;

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
	t_chunk_type	type;
	t_coord_i32		coord;
	t_texture		*north;
	t_texture		*east;
	t_texture		*west;
	t_texture		*south;
	t_texture		*ceiling;
	t_texture		*floor;
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
# define OPT_E_DEFAULT		'.'

/**
 * Collectible macro
 */
# define E_COLLECTIBLE		'C'
# define OPT_C_AMMO			'A'
# define OPT_C_HEALTH		'H'

/**
 * Door macro
 */
# define E_DOOR				'D'
# define OPT_D_N			'N'
# define OPT_D_E			'E'

/**
 * Furniture macro
 */
# define E_FURNITURE		'F'

typedef struct s_map
{
	uint32_t	height;
	uint32_t	width;
	t_coord_i32	size;
	t_vec		tex_list;
	t_vec		map;
}				t_map;

typedef struct s_game {
	t_param			param;
	t_player		player;
	t_map			map;
	t_hooks			hooks;
	void			*parser_data;
	int				return_value;
}	t_game;

/* ************************************************************************** */

#endif /* CUBE3D_H */