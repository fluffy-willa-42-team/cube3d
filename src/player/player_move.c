/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:18:47 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 13:02:25 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <math.h>

#include "mlx_utils.h"

t_wall_inter	get_wall(t_game *game, t_coord_f64 inter);

int	is_a_wall_move(t_wall_inter inter)
{
	if (inter.text1 && !(inter.text1->type & NO_CLIP))
		return (1);
	if (inter.text2 && !(inter.text2->type & NO_CLIP))
		return (1);
	return (0);
}

static t_coord_f64	get_pos_x(t_coord_f64 pos, double incre)
{
	return (set_f64(
			(int) pos.x + (int []){0, 1}[incre > 0],
		pos.y)
	);
}

static t_coord_f64	get_pos_y(t_coord_f64 pos, double incre)
{
	return (set_f64(
			pos.x,
			(int) pos.y + (int []){0, 1}[incre > 0]
	));
}

void	move_player(t_game *game, t_coord_f64 player, t_coord_f64 incre)
{
	if ((int) player.x == (int)(player.x + incre.x)
		|| !is_a_wall_move(get_wall(game, get_pos_x(player, incre.x))))
		game->player.pos.x += incre.x;
	if ((int) player.y == (int)(player.y + incre.y)
		|| !is_a_wall_move(get_wall(game, get_pos_y(player, incre.y))))
		game->player.pos.y += incre.y;
}
