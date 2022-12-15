/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:20:21 by mahadad           #+#    #+#             */
/*   Updated: 2022/12/15 11:36:37 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "cube3d_debug.h"

/* ft_isdigit */
#include "lib_is_check.h"

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Set the value of the current channel. And check if the value is good.
 * 
 * @param color Pointer to the channel variable.
 * @param channel 
 * @return int 
 */
static int	set_channel(int *channel, char *color)
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
 * @author @Matthew-Dreemurr
 * 
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

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Convert `r, g, b` to a int.
 */
static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Set the `channel->{r,g,b,a}`  structure from the `data->path`
 *        and check if the value is good.
 * 
 * @param tex 
 * @param channel 
 * @return int 
 */
static int	set_rgba_channel(t_texture *tex, t_color *channel)
{
	char	*color;

	color = tex->path;

	if (set_channel(&(channel->r), color))
		return (ret_print(EXIT_FAILURE, ERR_COLOR_R));
	color = get_next_channel(color);
	if (set_channel(&(channel->g), color))
		return (ret_print(EXIT_FAILURE, ERR_COLOR_G));
	color = get_next_channel(color);
	if (set_channel(&(channel->b), color))
		return (ret_print(EXIT_FAILURE, ERR_COLOR_B));
	color = get_next_channel(color);
	if (set_channel(&(channel->a), color))
		return (ret_print(EXIT_FAILURE, ERR_COLOR_A));
	return (EXIT_SUCCESS);
}

/**
 * @author @Matthew-Dreemurr
 * 
 * @brief Convert the raw color from the config file to int `rgb` and check if 
 *        the value is valid.
 */
int	set_color_texture(t_texture *tex)
{
	t_color	channel;

	set_rgba_channel(tex, &channel);
	tex->color = get_rgba(channel.r, channel.g, channel.b, channel.a);
	return (EXIT_SUCCESS);
}
