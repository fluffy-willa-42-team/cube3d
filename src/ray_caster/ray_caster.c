/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:01:39 by awillems          #+#    #+#             */
/*   Updated: 2022/11/01 10:37:47 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <stdio.h>

#include "mlx_utils.h"

double loop_len(double n, double len);
t_intersect get_intersect(t_game *game, t_coord_f64 player, double alpha);

uint32_t get_color_for_direction(const t_intersect inter)
{
	if (inter.wall.x - 0.00001 < inter.point.x && inter.point.x < inter.wall.x + 0.00001)
		return (0xeb4034FF);
	if (inter.wall.x + 0.99999 < inter.point.x && inter.point.x < inter.wall.x + 1.00001)
		return (0x4287f5FF);
	if (inter.wall.y - 0.00001 < inter.point.y && inter.point.y < inter.wall.y + 0.00001)
		return (0xfcba03FF);
	if (inter.wall.y + 0.99999 < inter.point.y && inter.point.y < inter.wall.y + 1.00001)
		return (0x32a852FF);
	return (0);
}

void ray_caster(t_game *game)
{
	const uint32_t fov_width = WIN_WIDTH / 4;
	const double alpha_incre = PI / 3 / fov_width;
	const t_coord_i32 pixel = set_i32(4, 128);

	for (uint32_t i = 0; i < fov_width; i++)
	{
		t_intersect inter = get_intersect(game, game->player.coord,
			loop_len(game->player.alpha - PI / 6 + alpha_incre * i, PI2));
		draw_rectangle(&game->param, set_f64(i * 4, WIN_HEIGHT - 128), pixel, 
			get_color_for_direction(inter));
	}
}