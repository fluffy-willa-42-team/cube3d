/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:01:39 by awillems          #+#    #+#             */
/*   Updated: 2022/11/20 12:47:19 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"

#include <stdio.h>

double	prot_tan(double alpha);
double	loop_len(double n, double len);
double	get_distance(t_game *game, t_inter *inter);
t_inter	get_intersect(t_game *game, t_coord_f64 player, double alpha, double tan_a);

void	draw_skybox(t_game *game);
void	draw_floor(t_game *game, int x, double alpha, double heigth_drawn, double dist);
void	draw_wall(t_game *game, t_inter *inter, uint32_t x, uint32_t height);
void	draw_transparent_wall(t_game *game, t_inter *inter, double alpha, double tan_a);

/**
 * @brief Will calculate the wall intersection draw the wall then the ground and
 * ceiling then draw the last transparent wall.
 * 
 * @param game Pointer to the game instance.
 * @param x The coordinate x of the column of the screen
 * @param alpha The angle at which we are looking at that column
 * @param tan_a The tangent of alpha
 */
void draw_column(t_game *game, uint32_t x, double alpha, double tan_a)
{
	t_inter	inter;
	double	dist;
	double	height_to_draw;
	
	inter = get_intersect(game, game->player.coord, loop_len(alpha, PI2), tan_a);
	dist = get_distance(game, &inter);
	height_to_draw = HEIGTH_OF_BLOCK * game->param.hob_mult / dist;
	draw_wall(game, &inter, x, height_to_draw);
	if (height_to_draw < game->stat.middle_screen_y - 1)
		draw_floor(game, x, alpha, height_to_draw, dist);
	draw_transparent_wall(game, &inter, alpha, tan_a);
}

/**
 * @brief Will draw onto the image (game.param.image) and preform a simple 2.5d
 * algorythm called ray casting to determine every pixel on the screen

 * @param game Pointer to the game instance.

 * @note Brief Explonation of the Ray Casting :

Ray Casting can be subdivised in 4 step :
 1.	Dray a line at the middle of the screen which each pixel is an intersection
	of the wall it finds. This step is more easy to do from a 2d perspective from
	the top, which is like a minimap from a top bottom perspective.
 2.	For each pixel on the line we have drown extend it based on the distance of
	the intersection of the wall. The further it is, the small the wall is.
 3.	The third step is to fill in the rest which is the ceiling and the floor.
 4.	(Optional) The last step is to draw every transparent wall on top of what we
	have drown.

All of these steps are done on a column but column basis.

 */
void ray_caster(t_game *game)
{
	double	tan_a;
	double	alpha;
	
	alpha = game->player.alpha - game->stat.fov_angle_1_2 - game->stat.fov_incre;
	for (uint32_t i = 0; i < WIN_WIDTH; i++)
	{
		alpha += game->stat.fov_incre;
		tan_a = prot_tan(alpha);
		draw_column(game, i, alpha, tan_a);
	}
}
