/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:28:36 by awillems          #+#    #+#             */
/*   Updated: 2022/11/15 12:05:38 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_texture *init_image(t_texture *ptr, const char *path)
{
	xpm_t *xpm_file = mlx_load_xpm42(path);
	if (!xpm_file)
		return (NULL);
	ptr->type = IMAGE | VALID;
	ptr->image = &xpm_file->texture;
	return (ptr);
}

t_texture *init_color(t_texture *ptr, uint32_t color)
{
	ptr->type = COLOR | VALID;
	ptr->color = color;
	return (ptr);
}