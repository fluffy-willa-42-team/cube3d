/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:02:42 by awillems          #+#    #+#             */
/*   Updated: 2022/10/25 11:02:42 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTER_H
# define RAY_CASTER_H

/* ************************************************************************** */

# include "cube3d.h"

/* ************************************************************************** */

//							0xAARRGGBB
# define COLOR_RAY			0x00fcba03
# define COLOR_SIDE			0x0021634c
# define COLOR_BACKGROUND	0x00222222
# define COLOR_PLAYER		0x00FF00FF

/* ************************************************************************** */

void			draw_minimap(t_game *game);
void			ray_caster(t_game *game);

/* ************************************************************************** */

typedef struct s_wall_inter
{
	t_chunk		*chunk1;
	t_chunk		*chunk2;
	t_texture	*text1;
	t_texture	*text2;
}	t_wall_inter;

typedef struct s_intersect {
	t_coord_f64	point;
	int32_t		nb_step;
}	t_intersect;

typedef struct s_inter {
	t_coord_f64	point;
	t_intersect	x_inter;
	t_intersect	y_inter;
}	t_inter;

/* ************************************************************************** */

typedef struct s_draw_wall {
	uint32_t	x;
	double		height;
	int			recursive;
}	t_draw_wall;

typedef struct s_draw_pixel {
	t_coord_f64	ratio;
	double		offset;
	uint32_t	i;
}	t_draw_pixel;

typedef struct s_draw_trans {
	double		alpha;
	double		tan_a;
	uint32_t	x;
	t_intersect	(*func)(t_intersect a, double b, double c);
}	t_draw_trans;

typedef struct s_ang_param {
	double	alpha;
	double	tan_a;
}	t_ang_param;

typedef struct s_get_inter2 {
	double		alpha;
	double		tan_a;
	t_intersect	(*func)(t_intersect a, double b, double c);
}	t_get_inter2;

typedef struct s_get_inter {
	t_intersect	x_inter;
	t_intersect	y_inter;
	double		x_dist;
	double		y_dist;
}	t_get_inter;

/* ************************************************************************** */

t_chunk			*get_chunk(t_game *data, t_coord_i32 pos);
t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);

/* ************************************************************************** */

#endif /* RAY_CASTER_H */