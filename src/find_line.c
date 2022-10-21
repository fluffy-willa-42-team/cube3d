
#include "cube3d.h"

t_coord find_init_vertical(t_game *game, double delta)
{
	t_coord res;
	
	res.x = (int) game->p_x;
	if (game->p_dx > 0)
		res.x++;

	res.y = delta * (res.x - game->p_x) + game->p_y;
	return (res);
}

t_coord find_step_vertical(t_game *game, double delta, t_coord prev)
{
	t_coord res;

	res.x = prev.x + (int []){1, -1}[game->p_dx < 0];
	res.y = delta * (res.x - game->p_x) + game->p_y;
	return (res);
}

t_coord find_init_horizontal(t_game *game, double delta)
{
	t_coord res;
	
	res.y = (int) game->p_y;
	if (game->p_dy > 0)
		res.y++;

	res.x = (1 / delta) * (res.y - game->p_y) + game->p_x;
	return (res);
}

t_coord find_step_horizontal(t_game *game, double delta, t_coord prev)
{
	(void) map;
	t_coord res;

	res.y = prev.y + (int []){-1, 1}[game->p_dy > 0];
	res.x = (1 / delta) * (res.y - game->p_y) + game->p_x;
	return (res);
}

