/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:33:07 by awillems          #+#    #+#             */
/*   Updated: 2022/10/26 16:07:38 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdint.h>
# include <stddef.h>

/* ************************************************************************** */

typedef struct s_texture {
	int		type;
	char	*path;
	void	*image;
	int		color;
}	t_texture;

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

typedef struct s_chunk {
	t_coord_i32	coord;
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	t_texture	ceiling;
	t_texture	floor;
}	t_chunk;

# define E_EMPTY '.'

/**
 * Player macro
 */

# define	E_PLAYER			'P'
# define	OPT_P_NORTH			'N'
# define	OPT_P_SOUTH			'S'
# define	OPT_P_EAST			'E'
# define	OPT_P_WEST			'W'

/**
 * Enemy macro
 */
# define	E_ENEMY			'E'
# define	T_ENEMY_DEFAULT	'./TODO'
# define	OPT_E_DEFAULT	'.'

/**
 * Collectible macro
 */
# define	E_COLLECTIBLE	'C'
# define	OPT_C_AMMO		'A'
# define	OPT_C_HEALTH	'H'

/**
 * Door macro
 */
# define	E_DOOR			'D'
# define	OPT_D_N			'N'
# define	OPT_D_E			'E'

/**
 * Furniture macro
 */
# define	E_FURNITURE		'F'

typedef struct s_entity {
	int32_t		type;
	t_coord_f32	coord;
	int			nb_texture;
	t_texture	*texture;
}	t_entity;

typedef struct s_map {

}	t_map;

/* ************************************************************************** */

#endif /* CUBE3D_H */