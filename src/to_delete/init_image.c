/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:28:36 by awillems          #+#    #+#             */
/*   Updated: 2022/11/25 13:26:58 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_texture	*init_image(t_texture *ptr, const char *path)
{
	xpm_t	*xpm_file;

	xpm_file = mlx_load_xpm42(path);
	if (!xpm_file)
		return (NULL);
	ptr->type = IMAGE | VALID;
	ptr->image = &xpm_file->texture;
	return (ptr);
}

t_texture	*init_color(t_texture *ptr, uint32_t color)
{
	ptr->type = VALID;
	ptr->color = color;
	return (ptr);
}

t_texture	*init_texture(t_texture *ptr, int type, char *path, uint32_t color)
{
	xpm_t	*xpm_file;

	if (!ptr)
		return (NULL);
	ptr->type = type;
	if (type & IMAGE)
	{
		xpm_file = mlx_load_xpm42(path);
		if (!xpm_file)
			return (NULL);
		ptr->image = &xpm_file->texture;
	}
	else
		ptr->color = color;
	ptr->type |= VALID;
	return (ptr);
}
