/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:20:37 by awillems          #+#    #+#             */
/*   Updated: 2022/10/25 13:20:37 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

/* ************************************************************************** */

#include "cube3d.h"

/* ************************************************************************** */

void put_pixel(t_mlx_param *param, int32_t x, int32_t y, uint32_t color);
void draw_rectangle(t_mlx_param *param, t_coord_f64 point, t_coord_i32 size, uint32_t color);
void draw_line(t_mlx_param *param, t_coord_f64 a, t_coord_f64 b, int32_t color);

uint32_t	get_pixel_image(t_texture *texture, uint32_t x, uint32_t y, t_coord_f64 ratio);
void draw_image(t_game *game, t_texture *texture, t_coord_i32 pos, t_coord_i32 size);

/* ************************************************************************** */

#endif /* MLX_UTILS_H */