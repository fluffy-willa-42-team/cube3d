/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:51:50 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/28 14:04:26 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_utils.h"

#include "cube3d_debug.h"
#include "mlx_utils.h"

#include <stdio.h>//TODO REMOVE
/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Free all buffer from the parse that is not in use by the game engine.
 * //TODO #11 Free all allocated memory and open file/image.
 * 
 */
int	destroy_data(int ret, t_parser *data)
{
	int			i;
	t_texture	*tmp;

	i = '!' - 1;
	while (++i < 125)
	{
		tmp = get_tex_ptr(&data->tex_list, i);
		if (tmp && tmp->token && tmp->image)
			destroy_image(data->param.mlx, tmp->image);
	}
	if (!data)
		return (ret);
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
	return (ret);
}
