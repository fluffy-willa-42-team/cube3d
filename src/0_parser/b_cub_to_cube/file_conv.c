/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:52:08 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/02 13:03:01 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>
#include <stdio.h>//TODO REMOVE

/**
 * @brief Try to find all mandatory texture and convert to `.cube` format. Then
 *        convert map to `.cube` format.
 * 
 * @param data Parser structure
 * @return int Return 1 if the `c` is find in the `set` otherwise return 0. 
 */
static int	cub_to_cube(t_parser *data)
{
	data->cube = v_init_r(sizeof(char), NULL, NULL, 1000000);
	if (!v_alloc(&data->cube, SET, 5000000))
		return(ret_print(EXIT_FAILURE, "ERR_VEC_ALLOC"));
	if (texture_conv(data) || map_conv(data)/*//WIP*/)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @author Matthew-Dreemurr
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
	{
		if (cub_to_cube(data) || !v_delete(&data->cub)/* //TODO change check after the lib update ! */ /*//TODO REMOVE, free only in main*/)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
