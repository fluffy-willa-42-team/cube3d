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

# include "cube3d.h"

/* ************************************************************************** */

u_int32_t	put_pixel_in_image(t_image *texture,
				uint32_t x, uint32_t y, uint32_t color);
uint32_t	*get_pixel_from_image(t_texture *texture, uint32_t x, uint32_t y);
uint32_t	destroy_image(void *mlx, t_image *image);

void		put_pixel(t_game *game, int32_t x, int32_t y, uint32_t color);
void		draw_rectangle(t_game *game, t_coord_f64 point, t_coord_i32 size,
				uint32_t color);
void		draw_line(t_game *game, t_coord_f64 a, t_coord_f64 b,
				int32_t color);

void		draw_mini_rect(t_game *game, t_coord_f64 pos, uint32_t color);
void		draw_mini_point(t_game *game, t_coord_f64 pos, int size,
				uint32_t color);
void		draw_mini_line(t_game *game, t_coord_f64 a, t_coord_f64 b,
				int32_t color);

uint32_t	get_pixel_image(const t_texture *texture, uint32_t x, uint32_t y,
				t_coord_f64 ratio);
void		draw_image(t_game *game, t_texture *texture, t_coord_i32 pos,
				t_coord_i32 size);

/* ************************************************************************** */

#endif /* MLX_UTILS_H */