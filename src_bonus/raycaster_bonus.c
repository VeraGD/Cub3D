/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:44:53 by narrospi          #+#    #+#             */
/*   Updated: 2025/06/21 13:44:54 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	set_horizontal(t_data *data)
{
	double	dist;
	double	correction;
	double	result;

	if (data->rayc.y_dir == 1)
	{
		result = data->rayc.y_hit - data->player.y;
		data->rayc.wall_dist[data->rayc.slice] = result / data->rayc.y;
		data->rayc.hit_text = data->south[data->torch_frame];
	}
	else
	{
		result = data->rayc.y_hit - data->player.y + 1;
		data->rayc.wall_dist[data->rayc.slice] = result / data->rayc.y;
		data->rayc.hit_text = data->north[data->torch_frame];
	}
	dist = data->rayc.wall_dist[data->rayc.slice];
	correction = sqrt(data->rayc.x * data->rayc.x + \
		data->rayc.y * data->rayc.y);
	data->rayc.wall_dist[data->rayc.slice] = dist * correction;
	data->rayc.hit_portion = data->player.x + dist * data->rayc.x;
	data->rayc.hit_portion -= floor(data->rayc.hit_portion);
	if (data->rayc.y_dir == 1)
		data->rayc.hit_portion = 1.0 - data->rayc.hit_portion;
}

static void	set_vertical(t_data *data)
{
	double	dist;
	double	correction;
	double	result;

	if (data->rayc.x_dir == 1)
	{
		result = data->rayc.x_hit - data->player.x;
		data->rayc.wall_dist[data->rayc.slice] = result / data->rayc.x;
		data->rayc.hit_text = data->east[data->torch_frame];
	}
	else
	{
		result = data->rayc.x_hit - data->player.x + 1;
		data->rayc.wall_dist[data->rayc.slice] = result / data->rayc.x;
		data->rayc.hit_text = data->west[data->torch_frame];
	}
	dist = data->rayc.wall_dist[data->rayc.slice];
	correction = sqrt(data->rayc.x * data->rayc.x + \
		data->rayc.y * data->rayc.y);
	data->rayc.wall_dist[data->rayc.slice] = dist * correction;
	data->rayc.hit_portion = data->player.y + dist * data->rayc.y;
	data->rayc.hit_portion -= floor(data->rayc.hit_portion);
	if (data->rayc.x_dir == -1)
		data->rayc.hit_portion = 1.0 - data->rayc.hit_portion;
}

static void	get_distance(t_data *data)
{
	char	hit_horizontal;

	while (42)
	{
		if (data->rayc.x_dist < data->rayc.y_dist)
		{
			data->rayc.x_dist += data->rayc.x_delta;
			data->rayc.x_hit += data->rayc.x_dir;
			hit_horizontal = 0;
		}
		else
		{
			data->rayc.y_dist += data->rayc.y_delta;
			data->rayc.y_hit += data->rayc.y_dir;
			hit_horizontal = 1;
		}
		if (data->map->map[data->rayc.y_hit][data->rayc.x_hit] == WALL_C)
			break ;
	}
	if (hit_horizontal)
		set_horizontal(data);
	else
		set_vertical(data);
}

static void	calculate_ray(t_data *data)
{
	data->rayc.x = data->player.x_dir - \
		data->player.y_dir * data->rayc.shift_factor;
	data->rayc.y = data->player.y_dir + \
		data->player.x_dir * data->rayc.shift_factor;
	data->rayc.x_delta = fabs(1 / data->rayc.x);
	data->rayc.y_delta = fabs(1 / data->rayc.y);
	data->rayc.x_hit = data->player.x;
	data->rayc.y_hit = data->player.y;
	set_calculation(data);
}

void	raycastum(t_data *data)
{
	if (data->frame_count >= 20)
	{
		data->torch_frame = (data->torch_frame + 1) % 7;
		data->frame_count = 0;
	}
	data->rayc.slice = data->image->width;
	data->rayc.shift_factor = data->fov_projection;
	while (data->rayc.slice--)
	{
		calculate_ray(data);
		get_distance(data);
		draw_slice(data);
		data->rayc.shift_factor -= data->shift_distance;
	}
}
