/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:44:53 by narrospi          #+#    #+#             */
/*   Updated: 2025/06/21 13:44:54 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_calculation(t_data *d)
{
	if (d->rayc.x < 0)
	{
		d->rayc.x_dir = -1;
		d->rayc.x_dist = (d->player.x - d->rayc.x_hit) * d->rayc.x_delta;
	}
	else
	{
		d->rayc.x_dir = 1;
		d->rayc.x_dist = (d->rayc.x_hit + 1.0 - d->player.x) * d->rayc.x_delta;
	}
	if (d->rayc.y < 0)
	{
		d->rayc.y_dir = -1;
		d->rayc.y_dist = (d->player.y - d->rayc.y_hit) * d->rayc.y_delta;
	}
	else
	{
		d->rayc.y_dir = 1;
		d->rayc.y_dist = (d->rayc.y_hit + 1.0 - d->player.y) * d->rayc.y_delta;
	}
}
