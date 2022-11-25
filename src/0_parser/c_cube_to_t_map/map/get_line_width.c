/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:src/ray_caster/get_ray/get_distance.c
/*   get_distance.c                                     :+:      :+:    :+:   */
=======
/*   get_line_width.c                                   :+:      :+:    :+:   */
>>>>>>> main:src/0_parser/c_cube_to_t_map/map/get_line_width.c
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/ray_caster/get_ray/get_distance.c
/*   Created: 2022/11/20 12:43:53 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 12:32:31 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

double	get_distance(t_game *game, t_coord_f64 pos)
{
	return ((pos.x - game->player.pos.x) * game->player.cosin.x
		+ (pos.y - game->player.pos.y) * game->player.cosin.y);
=======
/*   Created: 2022/11/22 14:38:57 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/22 14:39:12 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Get the width of the current line.
 * 
 * @param data Parser structure.
 * @return int 
 */
int	get_line_width(t_parser *data)
{
	int	tmp;

	tmp = data->index;
	while (data->cube_map[tmp] && data->cube_map[tmp] != '\n')
		tmp++;
	return (tmp - data->index);
>>>>>>> main:src/0_parser/c_cube_to_t_map/map/get_line_width.c
}
