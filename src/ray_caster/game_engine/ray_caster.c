/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:01:39 by awillems          #+#    #+#             */
/*   Updated: 2022/11/15 12:25:50 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include <math.h>
#include <stdio.h>

double loop_len(double n, double len);
t_inter get_intersect(t_game *game, t_coord_f64 player, double alpha);

void	draw_skybox(t_game *game);
void	draw_floor(t_game *game, int x, double alpha, int heigth_drawn);
int32_t draw_wall(t_game *game, t_inter inter, uint32_t x, int32_t height);

static double distance(t_game *game, t_inter inter)
{
	return ((inter.point.x - game->player.coord.x) * game->player.cosin.x
		+ (inter.point.y - game->player.coord.y) * game->player.cosin.y);
}


void ray_caster(t_game *game)
{
	double	angle;
	t_inter	inter;
	double	dist;
	
	draw_rectangle(&game->param, set_f64(0, 0), set_i32(WIN_WIDTH, WIN_HEIGHT), 0x000000FF);
	angle = game->player.alpha - FOV_ANGLE1_2 - FOV_INCRE;
	for (uint32_t i = 0; i < WIN_WIDTH; i++)
	{
		angle += FOV_INCRE;
		//draw Walls
		inter = get_intersect(game, game->player.coord, loop_len(angle, PI2));
		dist = distance(game, inter);
		int heigth_drawn = draw_wall(game, inter, i, HEIGTH_OF_BLOCK * game->param.hob_mult / dist);
		if (heigth_drawn >= WIN_HEIGHT - 1)
			continue ;
		draw_floor(game, i, angle, heigth_drawn);
	}
}