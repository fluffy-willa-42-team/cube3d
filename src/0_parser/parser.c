/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:53:32 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/16 15:28:43 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include "lib_mem.h" /* ft_memcpy */

#include "cube3d_debug.h"

/**
 * @author Matthew-Dreemurr
 *
 * @brief Check if the file name have `.cub(e)`, try to open the file and store
 *        in the memory.
 *        If is a `.cub` file convert to `.cube`. Store the `.cube` in the
 *        t_map data structure.
 *        Finally set up the `map` structure pointer.
 * 
 * @param av Path of the map file to open and store in the t_map data structure.
 * @return int Return zero value, if there is a error return non zero value.
 */
int	parser(char *av, t_map *map)
{
	t_parser	data;

	struct_set(&data, sizeof(data));
	data.path = av;
	if (open_file(&data)
		|| read_file(&data)
		|| file_sani(&data)
		|| file_conv(&data)
		|| cube_to_t_map(&data))
		return (EXIT_FAILURE);
	if (!v_delete(&data.cube))/* //TODO change check after the lib update ! *///TODO REMOVE, free only in main
		return(EXIT_FAILURE);//TODO REMOVE, no safe
	map->map = data.map;
	map->size = data.map_size;
	map->width = data.map_size.x;
	map->height = data.map_size.y;
	return (EXIT_SUCCESS);
}
