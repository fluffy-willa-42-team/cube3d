/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:27:58 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/15 11:36:34 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* mlx_load_xpm42() */
#include "mlx.h"

/* get_tex_ptr() */
#include "cube3d_utils.h"

#include "cube3d_debug.h"

#include <stdio.h>//TODO REMOVE

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Replace the `'\n'` of a line with `\0'`.
 */
static void	null_terminate_line(char *line)
{
	while (*line && *line != ' ' && *line != '\n')
		line++;
	*line = '\0';
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Open xmp file from the `tex->path`
 * 
 */
static int	open_file_texture(t_param *param, t_texture *tex)
{
	char	*path;
	int		useless1;
	int		useless2;

	if (!tex || !tex->path)
		return (ret_print(EXIT_FAILURE, ERR_NULL_TEX));
	path = tex->path;
	null_terminate_line(path);
	tex->image = mlx_xpm_file_to_image(param->mlx, path, &useless1, &useless2);
	if (!tex->image)
		return (ret_print(EXIT_FAILURE, ERR_TEX_FILE));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Store the texture ptr of the skybox.
 */
static int	set_skybox(t_texture *tex, t_parser *data)
{
	tex->skybox_tex = get_tex_ptr(&data->tex_list, tex->sky_box_token);
	if (!tex->sky_box_token)
		return (ret_print(EXIT_FAILURE, ERR_SKY_TOKEN_FORMAT));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Check the type of the texture and call the rigth function to manage
 *        it.
 */
static int	init_texture_while(t_texture *tex, t_parser *data)
{
	if (tex->type & IMAGE)
	{
		if (open_file_texture(&data->param, tex))
			return (EXIT_FAILURE);
	}
	else if (tex->type & COLOR)
	{
		if (set_color_texture(tex))
			return (EXIT_FAILURE);
	}
	if (tex->sky_box_token && tex->sky_box_token != '.')
		if (set_skybox(tex, data))
			return (EXIT_FAILURE);
	tex->type |= VALID;
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Check the type of texture and open the file or convert the color.
 */
int	init_texture(t_parser *data)
{
	int			i;
	t_texture	*tex;

	i = 0;
	tex = data->tex_list.buffer;
	while (i < DEFAULT_CUBE_TEX_NB)
	{
		if (tex[i].token)
			if (init_texture_while(&tex[i], data))
				return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
