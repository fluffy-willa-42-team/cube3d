/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:04:32 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 13:22:59 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "mlx_utils.h"

void	draw_mini_rect(t_game *game, t_coord_f64 pos, uint32_t color)
{
	draw_rectangle(game,
		set_f64(pos.x * game->param.minimap_size,
			pos.y * game->param.minimap_size),
		set_i32(game->param.minimap_size, game->param.minimap_size),
		color
		);
}

void	draw_mini_point(t_game *game, t_coord_f64 pos, int size, uint32_t color)
{
	draw_rectangle(game,
		set_f64(pos.x * game->param.minimap_size - size,
			pos.y * game->param.minimap_size - size),
		set_i32(size * 2, size * 2),
		color
		);
}

void	draw_mini_line(t_game *game, t_coord_f64 a, t_coord_f64 b,
	int32_t color)
{
	draw_line(game,
		set_f64(a.x * game->param.minimap_size, a.y * game->param.minimap_size),
		set_f64(b.x * game->param.minimap_size, b.y * game->param.minimap_size),
		color
		);
}
