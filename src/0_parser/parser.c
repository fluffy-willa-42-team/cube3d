/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:53:32 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/30 10:58:33 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"
/* ft_memcpy */
#include "lib_mem.h"

#include <stdio.h>//TODO REMOVE

//TODO REMOVE
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

static void	print_tex(t_parser *data, char i)
{
	const t_texture	*tex = get_tex_ptr(&data->tex_list, i);

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
		"       token_ptr :  \'%c\',\n"
		"       *skybox_tex   :  [%p],\n"
		"       color         :  [0x%.8x]\n"
		"     }\n",
		(char)i, (tex), (tex->type & UNDEFINED) != 0, (tex->type & VALID) != 0,
		(tex->type & COLOR) != 0, (tex->type & IMAGE) != 0,
		(tex->type & SKYBOX) != 0, (tex->type & NO_CLIP) != 0,
		(tex->type & TRANSPARENCY) != 0, tex->token, tex->path, tex->image,
		tex->token_ptr, tex->skybox_tex, tex->color);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

int	tex_debug(t_parser *data)
{
	t_texture	*tmp;
	int			i;

	tmp = NULL;
	i = 0;
	while (i < 125)
	{
		tmp = get_tex_ptr(&data->tex_list, i);
		if (tmp && tmp->type > 0 && DEBUG_PARSE)
			print_tex(data, i);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	map_debug(t_parser *data)
{
	int32_t	x;
	int32_t	y;
	t_chunk	*chunk;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			chunk = get_chunk_pars(data, set_i32(x, y));
			if (!chunk || chunk->type == BAD_CHUNK)
				printf("!");
			if (chunk->type == WHITE_SPACE_CHUNK)
				printf(" ");
			if (chunk->type == GOOD_CHUNK)
				printf("0");
			x++;
		}
		y++;
		printf("\n");
	}
}

/**
 * @author @Matthew-Dreemurr
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
int	parser(char *av, t_parser *data)
{
	data->path = av;
	if (open_file(data)
		|| file_sani(data)
		|| file_conv(data)
		|| cube_to_t_map(data))
		return (EXIT_FAILURE);
	map_debug(data);
	tex_debug(data);
	return (EXIT_SUCCESS);
}
