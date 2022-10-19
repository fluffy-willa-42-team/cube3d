/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:33:07 by awillems          #+#    #+#             */
/*   Updated: 2022/10/19 15:42:27 by awillems         ###   ########.fr       */
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
	int32_t x;
	int32_t y;
	int32_t z;
}	t_coord_i32;

typedef struct s_coord_f32 {
	double x;
	double y;
	double z;
}	t_coord_f32;

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
	t_coord_f32	coord;
	int 		nb_texture;
	t_texture	*texture;
}	t_entity;

typedef struct s_map {

}	t_map;

/* ************************************************************************** */

#endif /* CUBE3D_H */