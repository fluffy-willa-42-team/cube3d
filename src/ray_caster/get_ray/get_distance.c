/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:43:53 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 15:50:11 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

double	get_distance(t_game *game, t_coord_f64 pos)
{
	return ((pos.x - game->player.pos.x) * game->player.cosin.x
		+ (pos.y - game->player.pos.y) * game->player.cosin.y);
}
