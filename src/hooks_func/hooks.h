/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 11:45:17 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 12:33:41 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

/* ************************************************************************** */

typedef enum e_status
{
	KEY_UP		= 0,
	KEY_DOWN	= 1,
}	t_status;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}	t_bool;

typedef enum e_dir
{
	FRONT	= 0b0001,
	BACK	= 0b0010,
	RIGHT	= 0b0100,
	LEFT	= 0b1000,
}	t_dir;

typedef struct s_hooks
{
	t_bool	exit;
	t_dir	dir;
	t_bool	minimap_scale_up;
	t_bool	minimap_scale_down;
	t_bool	map_scale_up;
	t_bool	map_scale_down;
}	t_hooks;

typedef struct s_keyset
{
	int		keycode;
	void	*ptr;
	int		value;
}	t_keyset;

/* ************************************************************************** */

#endif /* HOOKS_H */