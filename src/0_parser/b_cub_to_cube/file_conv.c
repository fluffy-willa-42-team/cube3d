/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:52:08 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/15 11:35:52 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Try to find all mandatory texture and convert to `.cube` format. Then
 *        convert map to `.cube` format.
 * 
 * @param data Parser structure
 * @return int Return 1 if the `c` is find in the `set` otherwise return 0. 
 */
static int	cub_to_cube(t_parser *data)
{
	data->cube = v_init(sizeof(char), NULL, NULL);
	if (!v_alloc(&data->cube, SET, 5000000))
		return (ret_print(EXIT_FAILURE, ERR_VEC_ALLOC));
	if (texture_conv(data) || map_conv(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Convert `.cub` to `.cube` format if need. Otherwise convert `.cube` to
 *        `t_map` structure.
 * 
 * @param data Parser structure
 * @return int Return 1 if the `c` is find in the `set` otherwise return 0.
 */
int	file_conv(t_parser *data)
{
	if (data->type == CUB_FILE)
		if (cub_to_cube(data))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
