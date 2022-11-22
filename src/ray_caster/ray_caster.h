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

#ifndef RAY_CASTER
# define RAY_CASTER

/* ************************************************************************** */

#include "cube3d.h"

/* ************************************************************************** */

int draw_minimap(t_game *game);
void ray_caster(t_game *game);

/* ************************************************************************** */

typedef struct s_gpiximg {
	t_coord_f64	ratio;
	int32_t		offset;
	int32_t		i;
}	t_gpiximg;

typedef struct s_inter {
	t_coord_f64 point;
	t_coord_i32 wall;
	int32_t		nb_step_x;
	int32_t		nb_step_y;
}	t_inter;

/**
 * @brief Structure for get Intersect
 * 
 * @param point Point of intersection
 */
typedef struct s_intersect {
	t_coord_f64 point;
	int32_t		nb_step;
}	t_intersect;

/* ************************************************************************** */

#endif /* RAY_CASTER */