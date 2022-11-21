/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:27:58 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/21 18:46:32 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* EXIT_SUCCESS, EXIT_FAILURE*/
#include <stdlib.h>

/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# include "MLX42.h"

#include "cube3d_debug.h"

#include "lib_is_check.h" /* ft_isdigit */

#include <stdio.h>//TODO REMOVE

static void	null_terminate_line(char *line)
{
	while (*line && *line != ' ' && *line != '\n')
		line++;
	*line = '\0';
}

static int	open_file_texture(t_texture *tex)
{
	char	*path;

	path = tex->path;
	null_terminate_line(path);
	printf("Open [%s]\n", path);//TODO REMOVE
	tex->image = mlx_load_xpm42(path);
	if (!tex->image)
		return (ret_print(EXIT_FAILURE, ERR_BAD_XPM));
	return (EXIT_SUCCESS);
}

/**
 * @brief Set the value of the current channel. And check if the value is good.
 * 
 * @param color Pointer to the channel variable.
 * @param channel 
 * @return int 
 */
static int	set_channel(char *color, int *channel)
{
	int	val;

	val = 0;
	if (*color == '-')
		return (EXIT_FAILURE);
	while (ft_isdigit(*color))
	{
		val += *color - '0';
		color++;
		if (ft_isdigit(*color))
			val *= 10;
		else
			break ;
	}
	if (val > 255)
		return (EXIT_FAILURE);
	*channel = val;
	return (EXIT_SUCCESS);
}

/**
 * @brief Return the address of the next channel.
 * 
 * 
 * @example
 *          Color format
 *             [0 ] r
 *             [1 ] r
 *             [2 ] r
 *             [3 ] ,
 *             [4 ] g
 *             [5 ] g
 *             [6 ] g
 *             [7 ] ,
 *             [8 ] b
 *             [9 ] b
 *             [10] b
 *             [11] ,
 *             [12] a
 *             [13] a
 *             [14] a
 * 
 * @param channel 
 * @return char* 
 */
static char	*get_next_channel(char *channel)
{
	while (*channel && ft_isdigit(*channel))
		channel++;
	if (*channel == ',')
		channel++;
	return (channel);
}

static int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @brief Set the `channel->{r,g,b,a}` structure and check if the value is good.
 * 
 * @param tex 
 * @param channel 
 * @return int 
 */
static int	set_channel(t_texture *tex, t_color *channel)
{
	char	*color;

	color = tex->path;

	if (set_channel(color, &(channel->r)))
		return (ret_print(EXIT_FAILURE, ERR_COLOR_R));
	color = get_next_channel(color);
	if (set_channel(color, &(channel->g)))
		return (ret_print(EXIT_FAILURE, ERR_COLOR_G));
	color = get_next_channel(color);
	if (set_channel(color, &(channel->b)))
		return (ret_print(EXIT_FAILURE, ERR_COLOR_B));
	color = get_next_channel(color);
	if (set_channel(color, &(channel->a)))
		return (ret_print(EXIT_FAILURE, ERR_COLOR_A));
	return (EXIT_SUCCESS);
}

static int	set_color_texture(t_texture *tex)
{
	t_color	channel;

	printf("Set [%.15s]\n", tex->path);//TODO REMOVE
	set_channel(tex, &channel);
	tex->color = get_rgba(channel.r, channel.g, channel.b, channel.a);
	return (EXIT_SUCCESS);
}

int	init_texture(t_parser *data)
{
	int			i;
	t_texture *tmp;

	i = 0;
	tmp = data->tex_list.buffer;
	while (i < DEFAULT_CUBE_TEX_NB)
	{
		if (tmp[i].token)
		{
			printf("init tex [%c]\n", tmp[i].token);
			if (tmp[i].type & IMAGE)
			{
				printf("Image\n");
				if (open_file_texture(&tmp[i]))
					return (EXIT_FAILURE);
			}
			else if (tmp[i].type & COLOR)
			{
				printf("Color\n");
				if (set_color_texture(&tmp[i]))
					return (EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}