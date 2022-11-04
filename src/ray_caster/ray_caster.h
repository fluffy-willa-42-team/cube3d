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

/* #####=====----------		Ray Caster In Program Var	 ----------=====##### */
// DONT TOUCH

# define FOV_ANGLE1_2		FOV_ANGLE / 2
# define FOV_WIDTH			WIN_WIDTH / COLUMN_WIDTH
# define FOV_INCRE			FOV_ANGLE * COLUMN_WIDTH / WIN_WIDTH
# define MAX_DIST			HEIGTH_OF_BLOCK / WIN_WIDTH

/* ************************************************************************** */

int draw_minimap(t_game *game);
void ray_caster(t_game *game);

typedef struct s_intersect {
	int			type;
	t_coord_f64 point;
	t_coord_i32 wall;
	t_coord_i32 prev_wall;
}	t_intersect;

/* ************************************************************************** */

#endif /* RAY_CASTER */