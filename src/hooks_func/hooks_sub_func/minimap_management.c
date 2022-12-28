/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:28:29 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 15:30:49 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	change_value_i(uint32_t *v, uint32_t x, uint32_t y, uint32_t z);
void	change_value_f(double *v, double x, double y, double z);

void	scale_minimap(t_game *game)
{
	if (game->hooks.minimap_scale_up && game->hooks.minimap_scale_down)
		return ;
	if (game->hooks.minimap_scale_up)
		change_value_i(&game->param.minimap_size, 1, 1,
			game->param.max_minimap_size);
	else if (game->hooks.minimap_scale_down)
		change_value_i(&game->param.minimap_size, -1, 1,
			game->param.max_minimap_size);
}

void	scale_player(t_game *game)
{
	if (game->hooks.player_scale_up && game->hooks.player_scale_down)
		return ;
	if (game->hooks.player_scale_up)
		change_value_f(&game->param.minimap_point_size, 1, 1, 100);
	else if (game->hooks.player_scale_down)
		change_value_f(&game->param.minimap_point_size, -1, 1, 100);
}
