/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:01:39 by awillems          #+#    #+#             */
/*   Updated: 2022/11/07 13:15:28 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"

double loop_len(double n, double len);
t_inter get_intersect(t_game *game, t_coord_f64 player, double alpha);

void draw_skybox(t_game *game);

void draw_simple(t_game *game, t_inter inter, uint32_t x, int32_t height);
void draw_column(t_game *game, t_inter inter, uint32_t x, int32_t height);

static double distance(t_game *game, t_inter inter)
{
	return ((inter.point.x - game->player.coord.x) * game->player.delta.x
		+ (inter.point.y - game->player.coord.y) * game->player.delta.y);
}

void ray_caster(t_game *game)
{
	draw_skybox(game);
	for (uint32_t i = 0; i < FOV_WIDTH; i++)
	{
		t_inter inter = get_intersect(game, game->player.coord,
			loop_len(game->player.alpha - FOV_ANGLE1_2 + FOV_INCRE * i, PI2));
		double dist = distance(game, inter);
		// if (dist < MAX_DIST)
		// 	dist = MAX_DIST;
		// draw_simple(game, inter, i * COLUMN_WIDTH, HEIGTH_OF_BLOCK / dist);
		draw_column(game, inter, i * COLUMN_WIDTH, HEIGTH_OF_BLOCK / dist);
	}
}