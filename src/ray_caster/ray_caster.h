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

typedef struct s_wall_inter
{
	t_chunk		*chunk1;
	t_chunk		*chunk2;
	t_texture	*text1;
	t_texture	*text2;
}	t_wall_inter;

typedef struct s_intersect {
	t_coord_f64 point;
	int32_t		nb_step;
}	t_intersect;

typedef struct s_inter {
	t_coord_f64 point;
	t_intersect xInter;
	t_intersect yInter;
}	t_inter;

/* ************************************************************************** */

#endif /* RAY_CASTER */