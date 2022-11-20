/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:43:53 by awillems          #+#    #+#             */
/*   Updated: 2022/11/20 12:47:12 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

double get_distance(t_game *game, t_inter *inter)
{
	return ((inter->point.x - game->player.coord.x) * game->player.cosin.x
		+ (inter->point.y - game->player.coord.y) * game->player.cosin.y);
}
