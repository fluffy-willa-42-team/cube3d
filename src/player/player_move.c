/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:18:47 by awillems          #+#    #+#             */
/*   Updated: 2022/11/18 10:27:13 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <stdio.h>

t_chunk *get_chunk(t_game *game, t_coord_i32 coord);

typedef struct s_mv_data {
	t_coord_i32	out_coord;
	t_texture	*in_texture;
	t_texture	*out_texture;
}	t_mv_data;

t_mv_data	get_move_data_x(t_game *game, t_coord_f64 player, t_chunk *in_chunk, double incr)
{
	t_mv_data		res;
	t_chunk			*out_chunk;

	if (incr < 0) // EAST
	{
		out_chunk = get_chunk(game, set_i32((int) player.x - 1, (int) player.y));
		res.in_texture = in_chunk->east;
		res.out_texture = out_chunk->west;
	}
	else // WEST
	{
		out_chunk = get_chunk(game, set_i32((int) player.x + 1, (int) player.y));
		res.in_texture = in_chunk->west;
		res.out_texture = out_chunk->east;
	}
	res.out_coord = out_chunk->coord;
	res.out_coord = out_chunk->coord;
	return (res);
}

t_mv_data	get_move_data_y(t_game *game, t_coord_f64 player, t_chunk *in_chunk, double incr)
{
	t_mv_data		res;
	t_chunk			*out_chunk;

	if (incr < 0) // NORTH
	{
		out_chunk = get_chunk(game, set_i32((int) player.x, (int) player.y - 1));
		res.in_texture = in_chunk->south;
		res.out_texture = out_chunk->north;
	}
	else // SOUTH
	{
		out_chunk = get_chunk(game, set_i32((int) player.x, (int) player.y + 1));
		res.in_texture = in_chunk->north;
		res.out_texture = out_chunk->south;
		res.out_coord = out_chunk->coord;
	}
	res.out_coord = out_chunk->coord;
	res.out_coord = out_chunk->coord;
	return (res);
}

void	move_player(t_game *game, t_coord_f64 player, double x_incr, double y_incr)
{
	t_chunk			*in_chunk = get_chunk(game, set_i32((int) player.x, (int) player.y));

	t_mv_data		data_x = get_move_data_x(game, player, in_chunk, x_incr);
	t_mv_data		data_y = get_move_data_y(game, player, in_chunk, y_incr);

	(void) data_x;
	(void) data_y;
	
	if (!data_x.in_texture && !data_x.out_texture)
		game->player.coord.x += x_incr;
	if (!data_y.in_texture && !data_y.out_texture)
		game->player.coord.y += y_incr;

}
