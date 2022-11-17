/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:35:07 by awillems          #+#    #+#             */
/*   Updated: 2022/11/17 14:36:17 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>

void pos2_hook(t_player *player, double incr_x, double incr_y, double size)
{
	player->coord.x += incr_x;
	if (player->coord.x < 0)
		player->coord.x += size;
	else if (player->coord.x >= size)
		player->coord.x -= size;
	player->coord.y += incr_y;
	if (player->coord.y < 0)
		player->coord.y += size;
	else if (player->coord.y > size)
		player->coord.y -= size;
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

