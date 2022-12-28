/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:01:07 by awillems          #+#    #+#             */
/*   Updated: 2022/10/25 11:01:07 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include "mlx_utils.h"

double		loop_len(double n, double len);

void		draw_side(t_game *game, int32_t x, int32_t y);
void		draw_ray(t_game *game, uint32_t color, double alpha);

void	draw_minimap(t_game *game)
{
	const t_map	*map = &game->map;
	t_coord_i32	iter;
	float		i;
	t_chunk		*chunk;

	iter = set_i32(-1, -1);
	while (++iter.x < (int) map->width)
	{
		iter.y = -1;
		while (++iter.y < (int) map->height)
		{
			chunk = get_chunk(game, set_i32(iter.x, iter.y));
			if (chunk && chunk->floor && chunk->floor->type & SKYBOX)
				draw_mini_rect(game, set_f64(iter.x, iter.y), COLOR_BACKGROUND);
		}
	}

	draw_ray(game, COLOR_RAY, game->player.alpha);
	i = 0.001;
	while (i < FOV_ANG_1_2)
	{
		draw_ray(game, COLOR_RAY, loop_len(game->player.alpha - i, PI2));
		draw_ray(game, COLOR_RAY, loop_len(game->player.alpha + i, PI2));
		i += 0.001;
	}
	iter = set_i32(-1, -1);
	while (++iter.x < (int) map->width)
	{
		iter.y = -1;
		while (++iter.y < (int) map->height)
		{
			draw_side(game, iter.x, iter.y);
		}
	}
	draw_mini_point(game, game->player.pos, game->param.player_size,
		COLOR_PLAYER);
}
