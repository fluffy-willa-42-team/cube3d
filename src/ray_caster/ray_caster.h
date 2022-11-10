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

# define FOV_ANGLE1_2		(double) (FOV_ANGLE) / 2
# define FOV_WIDTH			(double) (WIN_WIDTH) / COLUMN_WIDTH
# define FOV_INCRE			(double) (FOV_ANGLE) * COLUMN_WIDTH / WIN_WIDTH
# define MAX_DIST			(double) (HEIGTH_OF_BLOCK) / WIN_WIDTH
# define MDDL_SCRN_HGTH		WIN_HEIGHT / 2 

/* ************************************************************************** */

int draw_minimap(t_game *game);
void ray_caster(t_game *game);

typedef struct s_inter {
	t_coord_f64 point;
	t_coord_i32 wall;
}	t_inter;

/**
 * @brief Structure for get Intersect
 * 
 * @param point Point of intersection
 * @param wall Coordinate of the wall of intersection in the direction of player
 * @param prev_wall Coordinate of the wall of intersection in the reverse 
 * direction of player
 */
typedef struct s_intersect {
	t_coord_f64 point;
	t_coord_i32 wall;
	t_coord_i32 prev_wall;
}	t_intersect;

/* ************************************************************************** */

#endif /* RAY_CASTER */