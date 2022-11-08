/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:01:39 by awillems          #+#    #+#             */
/*   Updated: 2022/11/08 18:00:44 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include <math.h>
#include <stdio.h>

double loop_len(double n, double len);
t_inter get_intersect(t_game *game, t_coord_f64 player, double alpha);

void draw_skybox(t_game *game);

int32_t draw_wall(t_game *game, t_inter inter, uint32_t x, int32_t height);

static double distance(t_game *game, t_inter inter)
{
	return ((inter.point.x - game->player.coord.x) * game->player.delta.x
		+ (inter.point.y - game->player.coord.y) * game->player.delta.y);
}

void ray_caster(t_game *game)
{
	double	angle;
	t_inter	inter;
	double	dist;
	
	draw_skybox(game);
	angle = game->player.alpha - FOV_ANGLE1_2 - FOV_INCRE;
	for (uint32_t i = 0; i < FOV_WIDTH; i++)
	{
		angle += FOV_INCRE;
		//draw Walls
		inter = get_intersect(game, game->player.coord, loop_len(angle, PI2));
		dist = distance(game, inter);
		int heigth_drawn = draw_wall(game, inter, i, HEIGTH_OF_BLOCK / dist);

		if (heigth_drawn >= WIN_HEIGHT - 1)
			continue ;
		
		int rest_to_draw = MDDL_SCRN_HGTH - heigth_drawn + 1;
		for (int32_t j = 0; j < rest_to_draw; j++)
		{
			//draw Floors
			put_pixel(&game->param, i, WIN_HEIGHT - j, 0xFF00FFFF);
			//draw Ceiling
			put_pixel(&game->param, i, j, 0x5555FFFF);
		}
	}
}