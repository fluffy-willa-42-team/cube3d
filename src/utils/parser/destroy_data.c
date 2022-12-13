/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:51:50 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/13 11:04:55 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

#include "cube3d_debug.h"
#include "mlx_utils.h"

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

	tmp = 0;
	i = '!';
	while (i < 125)
	{
		tmp = get_tex_ptr(&data->tex_list, i);
		if (tmp && tmp->image)
			destroy_image(data->param.mlx, tmp->image);
		i++;
	}
	if (data)
	{
		if ((v_delete(&data->cub))
			|| v_delete(&data->cube)
			|| v_delete(&data->map)
			|| v_delete(&data->tex_list))
			ret_print(EXIT_FAILURE, ERR_FREE_MEME);
		if (data->param.mlx && data->param.img)
			destroy_image(data->param.mlx, data->param.img);
		if (data->param.mlx && data->param.win)
			mlx_destroy_window(data->param.mlx, data->param.win);
		if (data->param.mlx)
			free(data->param.mlx);
	}
	return (ret);
}
