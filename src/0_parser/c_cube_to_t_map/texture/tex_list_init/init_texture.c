/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:27:58 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/22 15:00:43 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "MLX42.h"

/* mlx_load_xpm42() */
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

	if (!tex || !tex->path)
		return (ret_print(EXIT_FAILURE, ERR_NULL_TEX));
	path = tex->path;
	null_terminate_line(path);
	tex->image = mlx_load_xpm42(path);
	if (!tex->image)
		return (ret_print(EXIT_FAILURE, ERR_EMPTY_FILE));
	return (EXIT_SUCCESS);
}


/**
 * @brief Check the type of texture and open the file or convert the color.
 */
int	init_texture(t_parser *data)
{
	int			i;
	t_texture	*tmp;

	i = 0;
	tmp = data->tex_list.buffer;
	while (i < DEFAULT_CUBE_TEX_NB)
	{
		if (tmp[i].token)
		{
			printf("init tex [%c]\n", tmp[i].token);//TODO REMOVE
			if (tmp[i].type & IMAGE)
			{
				if (open_file_texture(&tmp[i]))
					return (EXIT_FAILURE);
			}
			else if (tmp[i].type & COLOR)
			{
				if (set_color_texture(&tmp[i]))
					return (EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
