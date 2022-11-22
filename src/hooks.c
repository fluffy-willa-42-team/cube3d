/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:35:07 by awillems          #+#    #+#             */
/*   Updated: 2022/11/22 10:13:59 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>

double	prot_tan(double alpha);

void pos_hook(double incr_x, double incr_y, t_coord_f64 *move_vec)
{
	move_vec->x += incr_x;
	move_vec->y += incr_y;
}

void angle_hook(t_game *game, double incrementation)
{
	game->player.alpha += incrementation;
	if (game->player.alpha < 0)
		game->player.alpha += PI2;
	else if (game->player.alpha > PI2)
		game->player.alpha -= PI2;
	game->player.cosin.x = cos(game->player.alpha);
	game->player.cosin.y = sin(game->player.alpha);
}

void	scale_hook(t_game *game, double incrementation)
{
	if (game->param.hob_mult + incrementation <= 100 && game->param.hob_mult + incrementation >= 0.5)
			game->param.hob_mult += incrementation;
}

void	map_hook(t_game *game, int32_t incrementation)
{
	if (game->param.minimap_size + incrementation <= 100 && game->param.minimap_size + incrementation >= 1)
		game->param.minimap_size += incrementation;
}

