/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:01:39 by awillems          #+#    #+#             */
/*   Updated: 2022/11/17 15:33:40 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"
#include <math.h>
#include <stdio.h>

double loop_len(double n, double len);
t_inter get_intersect(t_game *game, t_coord_f64 player, double alpha);

void	draw_skybox(t_game *game);
void	draw_floor(t_game *game, int x, double alpha, double heigth_drawn, double dist);
int32_t draw_wall(t_game *game, t_inter inter, uint32_t x, int32_t height);

static double distance(t_game *game, t_inter inter)
{
	return ((inter.point.x - game->player.coord.x) * game->player.cosin.x
		+ (inter.point.y - game->player.coord.y) * game->player.cosin.y);
}

void ray_caster(t_game *game)
{
	double	alpha;
	t_inter	inter;
	double	dist;
	double	height_to_draw = HEIGTH_OF_BLOCK * game->param.hob_mult;
	
	draw_rectangle(&game->param, set_f64(0, 0), set_i32(WIN_WIDTH, WIN_HEIGHT), 0x000000FF); // TODO FIX BLACK DEATH SPREADING WHEN CLOSE TO WALLS
	alpha = game->player.alpha - game->stat.fov_angle_1_2 - game->stat.fov_incre;
	for (uint32_t i = 0; i < WIN_WIDTH; i++)
	{
		alpha += game->stat.fov_incre;
		inter = get_intersect(game, game->player.coord, loop_len(alpha, PI2));
		dist = distance(game, inter);
		height_to_draw = HEIGTH_OF_BLOCK * game->param.hob_mult / dist;
		draw_wall(game, inter, i, height_to_draw);
		if (height_to_draw >= game->stat.middle_screen_y)
			continue ;
		draw_floor(game, i, alpha, height_to_draw - 1, dist);
	}
}