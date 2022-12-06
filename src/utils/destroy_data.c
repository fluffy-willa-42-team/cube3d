/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:51:50 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/06 14:27:15 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include "cube3d_debug.h"
#include <stdio.h>//TODO REMOVE
/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Free all buffer from the parse that is not in use by the game engine.
 * 
 */
int	destroy_data(int ret, t_parser *data)
{
	//TODO #11 Free all allocated memory and open file/image.
	int i;
	t_texture *tmp;

	i = '!';
	if (data->tex_list.buffer)
		while (i < 125)
		{
			printf("[%c]\n", i);
			tmp = get_tex_ptr(&data->tex_list, i);
			if (tmp && tmp->token && tmp->image)
				mlx_delete_texture(tmp->image);
			i++;
		}
	if ((v_delete(&data->cub))
		|| v_delete(&data->cube)
		|| v_delete(&data->map)
		|| v_delete(&data->tex_list))
	ret_print(EXIT_FAILURE, ERR_FREE_MEME);
	return (ret);
}
