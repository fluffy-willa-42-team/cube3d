/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:29:26 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 15:31:00 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	change_value_f(double *v, double x, double y, double z);

void	scale_map(t_game *game)
{
	if (game->hooks.map_scale_up && game->hooks.map_scale_down)
		return ;
	if (game->hooks.map_scale_up)
		change_value_f(&game->param.hob_mult, 0.05, 0.5, 100);
	else if (game->hooks.map_scale_down)
		change_value_f(&game->param.hob_mult, -0.05, 0.5, 100);
}
