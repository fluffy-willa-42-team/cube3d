/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:53:32 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/26 12:29:58 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/* ft_memcpy */
#include "lib_mem.h"

#include "cube3d_debug.h"

#include "MLX42.h"


#include <stdio.h>//TODO REMOVE

//TODO REMOVE
/******************************************************************************/
/* */ // Get the red channel.
/* */ int get_r(int rgba)
/* */ {
/* */     // Move 3 bytes to the right and mask out the first byte.
/* */     return ((rgba >> 24) & 0xFF);
/* */ }
/* */ 
/* */ // Get the green channel.
/* */ int get_g(int rgba)
/* */ {
/* */     // Move 2 bytes to the right and mask out the first byte.
/* */     return ((rgba >> 16) & 0xFF);
/* */ }
/* */ 
/* */ // Get the blue channel.
/* */ int get_b(int rgba)
/* */ {
/* */     // Move 1 byte to the right and mask out the first byte.
/* */     return ((rgba >> 8) & 0xFF);
/* */ }
/* */ 
/* */ // Get the alpha channel.
/* */ int get_a(int rgba)
/* */ {
/* */     // Move 0 bytes to the right and mask out the first byte.
/* */     return (rgba & 0xFF);
/* */ }
/******************************************************************************/


int	tex_debug(t_parser *data)
{
	int tmp = 0;
	for (int i = '!'; i < 125; i++)
	{
		tmp = get_tex_ptr(&data->tex_list, i)->type;
		if (tmp > 0)
			printf(
			"[%c][%p] {\n"
			"       type          :  {\n"
			"                          UNDEFINED     [%d]\n"
			"                          VALID         [%d]\n"
			"                          COLOR         [%d]\n"
			"                          IMAGE         [%d]\n"
			"                          SKYBOX        [%d]\n"
			"                          ALLOW_CLIP    [%d]\n"
			"                          TRANSPARENCY  [%d]\n"
			"                        },\n"
			"       token         :  \'%c\',\n"
			"       *path         :  \"%.15s\",\n"
			"       *image        :  [%p],\n"
			"       sky_box_token :  \'%c\',\n"
			"       *skybox_tex   :  [%p],\n"
			"       color         :  [%d, %d, %d, %d]\n"
			"     }\n",
			(char)i,
			(get_tex_ptr(&data->tex_list, i)),

			(get_tex_ptr(&data->tex_list, i)->type & UNDEFINED) != 0,
			(get_tex_ptr(&data->tex_list, i)->type & VALID) != 0,
			(get_tex_ptr(&data->tex_list, i)->type & COLOR) != 0,
			(get_tex_ptr(&data->tex_list, i)->type & IMAGE) != 0,
			(get_tex_ptr(&data->tex_list, i)->type & SKYBOX) != 0,
			(get_tex_ptr(&data->tex_list, i)->type & ALLOW_CLIP) != 0,
			(get_tex_ptr(&data->tex_list, i)->type & TRANSPARENCY) != 0,
			
			get_tex_ptr(&data->tex_list, i)->token,
			get_tex_ptr(&data->tex_list, i)->path,
			get_tex_ptr(&data->tex_list, i)->image,

			
			get_tex_ptr(&data->tex_list, i)->sky_box_token,
			get_tex_ptr(&data->tex_list, i)->skybox_tex,

			get_r(get_tex_ptr(&data->tex_list, i)->color),
			get_g(get_tex_ptr(&data->tex_list, i)->color),
			get_b(get_tex_ptr(&data->tex_list, i)->color),
			get_a(get_tex_ptr(&data->tex_list, i)->color));
	}
	return (EXIT_SUCCESS);
}

int	destroy_data(t_parser *data)
{
	//TODO #11 Free all allocated memory and open file/image.
	(void)data;
	return (EXIT_FAILURE);
}

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
		return (destroy_data(&data));
	map->map = data.map;
	map->width = data.map_width;
	map->height = data.map_height;
		/*TODO REMOVE*/tex_debug(&data);/*TODO REMOVE*/
	return (EXIT_SUCCESS);
}
