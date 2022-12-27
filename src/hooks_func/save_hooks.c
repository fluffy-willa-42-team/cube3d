/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 11:44:48 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 13:06:50 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "ray_caster.h"
#include "mlx_utils.h"
#include "key_macro.h"
#include <stdio.h>

int	save_hooks_var_change(const t_keyset *config, int keycode, int status)
{
	int	i;

	i = 0;
	while (i < NB_ASSIGNED_KEYS)
	{
		if (keycode == config[i].keycode)
		{
			if (status == KEY_DOWN)
				*(int *) config[i].ptr |= config[i].value;
			else if (status == KEY_UP)
				*(int *) config[i].ptr &= ~config[i].value;
			return (1);
		}
		i++;
	}
	return (0);
}

int	save_hooks(int keycode, t_game *game, int status)
{
	const t_keyset	config[NB_ASSIGNED_KEYS] = {
	{KEY_ESCAPE,	&game->hooks.exit,	TRUE},
	{KEY_W,			&game->hooks.dir,	FRONT},
	{KEY_S,			&game->hooks.dir,	BACK},
	{KEY_A,			&game->hooks.dir,	RIGHT},
	{KEY_D,			&game->hooks.dir,	LEFT},
	{KEY_Q,			&game->hooks.look_left,					TRUE},
	{KEY_E,			&game->hooks.look_right,				TRUE},
	{KEY_R,			&game->hooks.add_speed,					TRUE},
	{KEY_F,			&game->hooks.reduce_speed,				TRUE},
	{KEY_O,			&game->hooks.minimap_scale_up,			TRUE},
	{KEY_L,			&game->hooks.minimap_scale_down,		TRUE},
	{KEY_I,			&game->hooks.map_scale_up,				TRUE},
	{KEY_K,			&game->hooks.map_scale_down,			TRUE},
	{KEY_U,			&game->hooks.minimap_player_scale_up,	TRUE},
	{KEY_J,			&game->hooks.minimap_player_scale_down,	TRUE},
	};

	return (save_hooks_var_change(config, keycode, status));
}

int	save_hooks_up(int keycode, t_game *game)
{
	return (save_hooks(keycode, game, KEY_UP));
}

int	save_hooks_down(int keycode, t_game *game)
{
	return (save_hooks(keycode, game, KEY_DOWN));
}

// 	else if (keycode == KEY_Q)				speed_hook(game, 0.01);
// 	else if (keycode == KEY_E)				speed_hook(game, -0.01);