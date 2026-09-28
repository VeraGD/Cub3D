/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:43:09 by narrospi          #+#    #+#             */
/*   Updated: 2025/06/20 19:43:12 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	key_moves(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		data->player.front = 1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		data->player.front = 0;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		data->player.front = -1;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		data->player.front = 0;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		data->player.side = 1;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		data->player.side = 0;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		data->player.side = -1;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		data->player.side = 0;
	return ;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		close_window(data);
		return ;
	}
	else
		key_moves(keydata, data);
	return ;
}

void	mouse_rotation(void *param)
{
	t_data	*data;
	int32_t	mouse_x;
	int32_t	mouse_y;
	int32_t	delta_x;

	data = (t_data *)param;
	delta_x = 0;
	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
	delta_x = mouse_x - data->last_mouse_x;
	if (delta_x != 0)
	{
		data->last_mouse_x = mouse_x;
		data->player.turn = delta_x * 0.0025;
		delta_x = 0;
	}
	else
		data->player.turn = 0;
}
