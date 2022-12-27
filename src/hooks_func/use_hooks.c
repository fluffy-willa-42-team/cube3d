/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awillems <awillems@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:13:06 by awillems          #+#    #+#             */
/*   Updated: 2022/12/27 13:15:45 by awillems         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>

int	use_hooks(t_game *game)
{
	(void) game;
	printf("Use Keys...\n");
	return (1);
}
