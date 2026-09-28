/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:30:50 by narrospi          #+#    #+#             */
/*   Updated: 2025/05/29 14:33:22 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	animation_wand(t_data *data)
{
	char	*wand_num;

	wand_num = "0121\0";
	data->wand_img[data->wand_frame]->enabled = false;
	data->index = (data->index + 1) % 4;
	data->wand_frame = wand_num[data->index] - '0';
	data->wand_img[data->wand_frame]->enabled = true;
	data->wand_frame_count = 0;
}

static void	get_frame(void *param)
{
	t_data	*data;

	mouse_rotation(param);
	data = (t_data *)param;
	if (data->player.turn)
	{
		data->player.angle_dir += data->player.turn;
		data->player.x_dir = cos(data->player.angle_dir);
		data->player.y_dir = sin(data->player.angle_dir);
	}
	data->frame_count += 1;
	if (data->player.front || data->player.side)
		move_player(data, 0.0, 0.0);
	raycastum(data);
	draw_minimap(data, 0);
	data->wand_frame_count++;
	if (data->wand_frame_count >= 30)
		animation_wand(data);
}

void	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data && data->mlx)
	{
		free_structs(data->map, data);
		printf("You closed the game\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_error("Error allocating memory for data structure", data);
	data->checker = 0;
	check_parameters(ac, av, data);
	data->checker = 0;
	ini_imgs(data);
	data->map = ini_map(data);
	mlx_get_mouse_pos(data->mlx, &data->last_mouse_x, &data->last_mouse_y);
	map_parsing(av[1], data->map, data);
	find_player(data, data->map);
	init_minimap(data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
		ft_error("Error putting image to window", data);
	data->image->instances[0].z = 0;
	mlx_close_hook(data->mlx, close_window, data);
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_loop_hook(data->mlx, &get_frame, data);
	mlx_loop(data->mlx);
	free_structs(data->map, data);
	return (0);
}
