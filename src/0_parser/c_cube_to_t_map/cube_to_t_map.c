/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_to_t_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:12:15 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/08 17:22:41 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d.h"

#include "cube3d_debug.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include <stdio.h>//TODO REMOVE

#include "cube3d_utils.h"

/**
 * TODO
 * 
 * Parse tex and store
 *     - [x] Store in tex_array
 *     - [ ] Check for dup
 *     - [ ] Open tex file
 * Parse map and find HxW
 * 
 * Alloc array map
 * 
 * Init array map
 *     - [ ] Make a function that find chunk with x,y and init a struct in data.
 *           read_chunk(t_data *data.(tmp_)chunk_struct, int x, int y)
 *           t_chunk_struct {TOP,BOTTOM,N,S,E,W,C,F,ENTITY,TAG,...}
 * 
 */


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

/**
 * @brief 
 * 
 * @param data 
 * @return int 
 */
int	cube_to_t_map(t_parser *data)
{
	if (store_texture(data, data->cube.buffer))
		return (EXIT_FAILURE);
	// t_texture *tmp = data->tex_list.buffer;
	for (int i = '!'; i < (DEFAUT_CUBE_TEX_NB + '0'); i++)
		if (get_tex_ptr(&data->tex_list, i)->type)
			printf("[%c] {\n    type :   %d,\n    token :  \'%c\',\n    *path :  \"%.10s\",\n    *image : [%p],\n    color :  [%d, %d, %d, %d]\n    }\n", (char)i, get_tex_ptr(&data->tex_list, i)->type, get_tex_ptr(&data->tex_list, i)->token, get_tex_ptr(&data->tex_list, i)->path, get_tex_ptr(&data->tex_list, i)->image, get_r(get_tex_ptr(&data->tex_list, i)->color), get_g(get_tex_ptr(&data->tex_list, i)->color), get_b(get_tex_ptr(&data->tex_list, i)->color), get_a(get_tex_ptr(&data->tex_list, i)->color));
		// printf("[%lu] {\n    type :   %d,\n    token :  \'%c\',\n    *path :  \"%.10s\",\n    *image : [%p],\n    color :  [%d, %d, %d, %d]\n    }\n", i, (&tmp[i])->type, (&tmp[i])->token, (&tmp[i])->path, (&tmp[i])->image, get_r((&tmp[i])->color), get_g((&tmp[i])->color), get_b((&tmp[i])->color), get_a((&tmp[i])->color));
	
	return (EXIT_SUCCESS);
}