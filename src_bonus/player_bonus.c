/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:05:58 by narrospi          #+#    #+#             */
/*   Updated: 2025/06/21 16:06:01 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	set_angle_dir(t_data *data)
{
	if (data->player.position == 'N')
		data->player.angle_dir = 1.5 * PI;
	else if (data->player.position == 'S')
		data->player.angle_dir = 0.5 * PI;
	else if (data->player.position == 'E')
		data->player.angle_dir = 2.0 * PI;
	else
		data->player.angle_dir = 1.0 * PI;
}

void	find_player(t_data *data, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == data->player.position)
			{
				data->player.x = j + 0.5;
				data->player.y = i + 0.5;
			}
			j++;
		}
		i++;
	}
	set_angle_dir(data);
	data->player.x_dir = cos(data->player.angle_dir);
	data->player.y_dir = sin(data->player.angle_dir);
}

int	is_wall(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (data->map->map[map_y][map_x] == WALL_C)
		return (1);
	return (0);
}

static void	player_still_moving(t_data *data, double next_x, double next_y)
{
	double	check_x;
	double	check_y;

	check_x = next_x;
	check_y = next_y;
	if (next_x > data->player.x)
		check_x = next_x + 0.2;
	else if (next_x < data->player.x)
		check_x = next_x - 0.2;
	if (next_y > data->player.y)
		check_y = next_y + 0.2;
	else if (next_y < data->player.y)
		check_y = next_y - 0.2;
	if (!is_wall(data, check_x, data->player.y)
		&& !is_wall(data, data->player.x, check_y))
	{
		data->player.x = next_x;
		data->player.y = next_y;
	}
}

void	move_player(t_data *data, double next_x, double next_y)
{
	next_x = data->player.x;
	next_y = data->player.y;
	if (data->player.front == 1)
	{
		next_x += data->player.x_dir * 0.1;
		next_y += data->player.y_dir * 0.1;
	}
	else if (data->player.front == -1)
	{
		next_x -= data->player.x_dir * 0.1;
		next_y -= data->player.y_dir * 0.1;
	}
	if (data->player.side == -1)
	{
		next_x -= data->player.y_dir * 0.1;
		next_y += data->player.x_dir * 0.1;
	}
	else if (data->player.side == 1)
	{
		next_x += data->player.y_dir * 0.1;
		next_y -= data->player.x_dir * 0.1;
	}
	player_still_moving(data, next_x, next_y);
}
