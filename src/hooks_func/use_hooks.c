/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:13:06 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 15:33:38 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		exit_game(t_game *game);

void	scale_map(t_game *game);
void	scale_player(t_game *game);
void	scale_minimap(t_game *game);
void	change_speed(t_game *game);
void	rotate_player(t_game *game);
void	move_player_hook(t_game *game, t_dir dir);

void	update_win(t_game *game);

int	use_hooks(t_game *game)
{
	if (game->hooks.exit)
		exit_game(game);
	if (game->hooks.add_speed || game->hooks.reduce_speed)
		change_speed(game);
	if (game->hooks.dir != 0)
		move_player_hook(game, game->hooks.dir);
	if (game->hooks.look_left || game->hooks.look_right)
		rotate_player(game);
	if (game->hooks.minimap_scale_up || game->hooks.minimap_scale_down)
		scale_minimap(game);
	if (game->hooks.player_scale_up || game->hooks.player_scale_down)
		scale_player(game);
	if (game->hooks.map_scale_up || game->hooks.map_scale_down)
		scale_map(game);
	update_win(game);
	return (1);
}
