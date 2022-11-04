/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:44:56 by awillems          #+#    #+#             */
/*   Updated: 2022/10/26 09:44:56 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_TYPES_H
# define CUBE_TYPES_H

/* ************************************************************************** */

typedef struct s_coord_i32 {
	int32_t x;
	int32_t y;
}	t_coord_i32;

typedef struct s_coord_f64 {
	double x;
	double y;
}	t_coord_f64;

/* ************************************************************************** */

t_coord_i32	init_i32(void);
t_coord_f64	init_f64(void);

t_coord_f64 set_f64(float x, float y);
t_coord_i32 set_i32(float x, float y);

t_coord_f64 add_f64(t_coord_f64 a, t_coord_f64 b);

int is_equal(double a, double b);

/* ************************************************************************** */

#endif /* CUBE_TYPES_H */

