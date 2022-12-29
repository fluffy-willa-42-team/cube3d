/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thenormforcedmetodothis.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:37:33 by awillems          #+#    #+#             */
/*   Updated: 2022/12/29 14:38:46 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THENORMFORCEDMETODOTHIS_H
# define THENORMFORCEDMETODOTHIS_H

/* ************************************************************************** */

# include "ray_caster.h"

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
	t_intersect	(*func)();
}	t_draw_trans;

typedef struct s_ang_param {
	double	alpha;
	double	tan_a;
}	t_ang_param;

typedef struct s_get_inter2 {
	double		alpha;
	double		tan_a;
	t_intersect	(*func)();
}	t_get_inter2;

typedef struct s_get_inter {
	t_intersect	x_inter;
	t_intersect	y_inter;
	double		x_dist;
	double		y_dist;
}	t_get_inter;

typedef struct s_draw_floor {
	t_coord_f64	cosin;
	double		cos_a_minus_pa;
	double		rest_to_draw;
	double		height_drawn;
}	t_draw_floor;

typedef struct s_draw_floor2 {
	double		dist;
	double		height_drawn;
}	t_draw_floor2;

/* ************************************************************************** */

#endif /* THENORMFORCEDMETODOTHIS_H */