/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:01:39 by awillems          #+#    #+#             */
/*   Updated: 2022/12/28 15:27:54 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"

double	prot_tan(double alpha);
double	loop_len(double n, double len);
double	get_distance(t_game *game, t_coord_f64 pos);
t_inter	get_intersect(t_game *game, double alpha, double tan_a);

void	draw_wall(t_game *game, uint32_t x, t_coord_f64 inter, double height);
void	draw_floor(t_game *game, int x, double alpha, double height_drawn,
			double dist);
void	draw_transparency(t_game *game, uint32_t x, t_inter inter, double alpha,
			double tan_a);

/**
 * @brief Will calculate the wall intersection draw the wall then the ground and
 * ceiling then draw the last transparent wall.
 * 
 * @param game Pointer to the game instance.
 * @param x The coordinate x of the column of the screen
 * @param alpha The angle at which we are looking at that column
 * @param tan_a The tangent of alpha
 */
void	draw_column(t_game *game, uint32_t x, double alpha, double tan_a)
{
	t_inter	inter;
	double	dist;
	double	height_to_draw;

	inter = get_intersect(game, loop_len(alpha, PI2), tan_a);
	dist = get_distance(game, inter.point);
	height_to_draw = WIN_HEIGHT / 10 * game->param.hob_mult / dist;
	draw_wall(game, x, inter.point, height_to_draw);
	if (height_to_draw < WIN_HEIGHT / 2 - 1)
		draw_floor(game, x, alpha, height_to_draw, dist);
	draw_transparency(game, x, inter, loop_len(alpha, PI2), tan_a);
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
void	ray_caster(t_game *game)
{
	const double	fov_incr = (double)(FOV_ANGLE) / WIN_WIDTH;
	double			tan_a;
	double			alpha;
	uint32_t		i;

	alpha = game->player.alpha - (FOV_ANGLE / 2) - fov_incr;
	i = 0;
	while (i < WIN_WIDTH)
	{
		alpha += fov_incr;
		tan_a = prot_tan(alpha);
		draw_column(game, i, alpha, tan_a);
		i++;
	}
}
