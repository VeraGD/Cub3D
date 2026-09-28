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

#include "../includes/cub3d.h"

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
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		data->player.turn = -0.025;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		data->player.turn = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		data->player.turn = 0.025;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		data->player.turn = 0;
	else
		key_moves(keydata, data);
	return ;
}
