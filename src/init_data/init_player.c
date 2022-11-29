/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:28:58 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 11:39:33 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "init_data.h"
#include <math.h>

t_player	init_player(t_direction dir, t_coord_i32 pos)
{
	t_player	player;

	player.pos = set_f64(pos.x + 0.5, pos.y + 0.5);
	if (dir == NORTH)
		player.alpha = PI3_2;
	else if (dir == SOUTH)
		player.alpha = PI1_2;
	else if (dir == EAST)
		player.alpha = 0;
	else if (dir == WEST)
		player.alpha = PI;
	player.alpha += 0.00001;
	player.cosin = set_f64(cos(player.alpha), sin(player.alpha));
	return (player);
}