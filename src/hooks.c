/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:35:07 by awillems          #+#    #+#             */
/*   Updated: 2022/11/17 19:50:24 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>

void	move_player(t_game *game, double x_incr, double y_incr);
double	prot_tan(double alpha);

void pos_hook(t_game *game, double incr_x, double incr_y)
{
	move_player(game, incr_x, incr_y);
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
	game->player.tan = prot_tan(game->player.alpha);
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

