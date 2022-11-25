/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:43:53 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 12:32:31 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

double	get_distance(t_game *game, t_coord_f64 pos)
{
	return ((pos.x - game->player.pos.x) * game->player.cosin.x
		+ (pos.y - game->player.pos.y) * game->player.cosin.y);
}
