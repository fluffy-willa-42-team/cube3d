/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:55:41 by mahadad           #+#    #+#             */
/*   Updated: 2022/11/15 15:57:02 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_UTILS_H
# define CUBE3D_UTILS_H

# include "cube3d.h"

void		*struct_set(void *var, int size);

int			authzed_chunk_char(int c);
int			authzed_cube_tex(int c);
int			find_tex_type(char *tex);
int			get_tex_index(char token);
t_texture	*get_tex_ptr(t_vec *tex, char token);

#endif /* CUBE3D_UTILS_H */
