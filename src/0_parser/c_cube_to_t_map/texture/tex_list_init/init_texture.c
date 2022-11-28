/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:27:58 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/28 14:00:50 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* mlx_load_xpm42() */
#include "MLX42.h"

/* get_tex_ptr() */
#include "cube3d_utils.h"

#include "cube3d_debug.h"

#include <stdio.h>//TODO REMOVE

static void	null_terminate_line(char *line)
{
	while (*line && *line != ' ' && *line != '\n')
		line++;
	*line = '\0';
}

/**
 * @brief Open xmp file from the `tex->path`
 * 
 */
static int	open_file_texture(t_texture *tex)
{
	char	*path;
	xpm_t	*tmp;

	if (!tex || !tex->path)
		return (ret_print(EXIT_FAILURE, ERR_NULL_TEX));
	path = tex->path;
	null_terminate_line(path);
	tmp = mlx_load_xpm42(path);
	if (!tmp)
		return (ret_print(EXIT_FAILURE, ERR_EMPTY_FILE));
	tex->image = &tmp->texture;
	return (EXIT_SUCCESS);
}

static int	set_skybox(t_texture *tex, t_parser *data)
{
	tex->skybox_tex = get_tex_ptr(&data->tex_list, tex->sky_box_token);
	if (!tex->sky_box_token)
		return (ret_print(EXIT_FAILURE, ERR_SKY_TOKEN_FORMAT));
	return (EXIT_SUCCESS);
}

static int	init_texture_while(t_texture *tex, t_parser *data)
{
	if (tex->type & IMAGE)
	{
		if (open_file_texture(tex))
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
