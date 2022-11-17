/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:18:47 by awillems          #+#    #+#             */
/*   Updated: 2022/11/17 19:57:05 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

t_intersect	get_init_x(t_coord_f64 player, t_coord_f64 delta, double alpha, double tan_a);
t_intersect	get_init_y(t_coord_f64 player, t_coord_f64 delta, double alpha, double tan_a);
int			is_wall(t_game *game, t_intersect *inter);

void	move_player(t_game *game, double x_incr, double y_incr)
{
	t_coord_f64 delta	= set_f64(
		game->player.coord.x - (int) game->player.coord.x,
		game->player.coord.y - (int) game->player.coord.y
	);
	t_intersect xIntersect = get_init_x(game->player.coord, delta, game->player.alpha, game->player.tan);
	t_intersect yIntersect = get_init_y(game->player.coord, delta, game->player.alpha, game->player.tan);
	
	if (!is_wall(game, &yIntersect))
		game->player.coord.x += x_incr;
	if (!is_wall(game, &xIntersect))
		game->player.coord.y += y_incr;
}


// t_coord_f64	backup = game->player.coord;
// if (new_pos.x >= game->map.width)
// 	new_pos.x -= game->map.width;
// else if (new_pos.x < 0)
// 	new_pos.x += game->map.width;
// if (new_pos.y >= game->map.height)
// 	new_pos.y -= game->map.height;
// else if (new_pos.y < 0)
// 	new_pos.y += game->map.height;
// (void) new_pos;
// if (game->map.array[(int) backup.y][(int) new_pos.x] != 1)
// 	game->player.coord.x = new_pos.x;
// if (game->map.array[(int) new_pos.y][(int) backup.x] != 1)
// 	game->player.coord.y = new_pos.y;