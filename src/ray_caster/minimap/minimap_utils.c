/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:02:04 by awillems          #+#    #+#             */
/*   Updated: 2022/12/29 14:40:07 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "thenormforcedmetodothis.h"
#include "mlx_utils.h"

double		prot_tan(double alpha);
t_inter		get_intersect(t_game *game, t_ang_param a);

void	draw_ray(t_game *game, uint32_t color, double alpha)
{
	double	tan_a;
	t_inter	test;

	tan_a = prot_tan(alpha);
	test = get_intersect(game, (t_ang_param){alpha, tan_a});
	draw_mini_line(game, game->player.pos, test.point, color);
}

void	draw_side(t_game *game, int32_t x, int32_t y)
{
	t_chunk	*chunk;

	chunk = get_chunk(game, set_i32(x, y));
	if (chunk->north)
		draw_mini_line(game, set_f64(x, y), set_f64(x + 1, y), COLOR_SIDE);
	if (chunk->south)
		draw_mini_line(game, set_f64(x, y + 1), set_f64(x + 1, y + 1),
			COLOR_SIDE);
	if (chunk->east)
		draw_mini_line(game, set_f64(x + 1, y), set_f64(x + 1, y + 1),
			COLOR_SIDE);
	if (chunk->west)
		draw_mini_line(game, set_f64(x, y), set_f64(x, y + 1), COLOR_SIDE);
}
