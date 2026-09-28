/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:29:16 by veragarc          #+#    #+#             */
/*   Updated: 2025/06/30 17:29:21 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	init_wand(t_data *data, int i)
{
	const char		*paths[4];
	mlx_texture_t	*texture;

	paths[0] = "./imgs/wand_spell1.png";
	paths[1] = "./imgs/wand_spell2.png";
	paths[2] = "./imgs/wand_spell3.png";
	paths[3] = "./imgs/wand_spell2.png";
	data->wand_img = (mlx_image_t **)malloc(sizeof(mlx_image_t *) * 4);
	if (!data->wand_img)
		ft_error("Error allocating wand images", data);
	while (i < 4)
	{
		texture = mlx_load_png(paths[i]);
		if (!texture)
			ft_error("Error loading wand PNG", data);
		data->wand_img[i] = mlx_texture_to_image(data->mlx, texture);
		mlx_delete_texture(texture);
		if (!data->wand_img[i])
			ft_error("Error converting texture to image", data);
		if (mlx_image_to_window(data->mlx, data->wand_img[i], 200, 25) < 0)
			ft_error("Error putting image to window", data);
		data->wand_img[i]->instances[0].z = 2;
		data->wand_img[i]->enabled = (i == 0);
		i++;
	}
}

void	init_minimap(t_data *data)
{
	uint32_t	mini_width;
	uint32_t	mini_height;

	data->mini = (t_mini *)malloc(sizeof(t_mini));
	if (!data->mini)
		ft_error("Error allocating memory", data);
	data->mini->mini_img_size = MINI_IMG_SIZE;
	data->mini->mini_player = MINI_PLAYER_SIZE;
	mini_width = ft_strlen(data->map->map[0]) * data->mini->mini_img_size;
	mini_height = ft_strlen_double(data->map->map) * data->mini->mini_img_size;
	data->min_img = mlx_new_image(data->mlx, mini_width, mini_height);
	if (!data->min_img)
		ft_error("Error creating mini image", data);
	draw_minimap(data, 0);
	if (mlx_image_to_window(data->mlx, data->min_img, 50, 50) < 0)
		ft_error("Error putting image to window", data);
	data->min_img->instances[0].z = 1;
	init_wand(data, 0);
}

static void	draw_player(t_data *data)
{
	int	player_size;
	int	px;
	int	py;

	player_size = data->mini->mini_img_size * data->mini->mini_player / 10;
	py = -player_size;
	while (py <= player_size)
	{
		px = -player_size;
		while (px <= player_size)
		{
			colouring(data->min_img, (int)
				(data->player.x * data->mini->mini_img_size) + px,
				(int)(data->player.y * data->mini->mini_img_size) + py,
				MINI_PLAYER_COLOUR);
			px++;
		}
		py++;
	}
}

static void	draw_mini_sub(t_data *data, uint32_t colour, int x, int y)
{
	int	x_sub;
	int	y_sub;

	x_sub = 0;
	while (x_sub < data->mini->mini_img_size)
	{
		y_sub = 0;
		while (y_sub < data->mini->mini_img_size)
		{
			colouring(data->min_img,
				x * data->mini->mini_img_size + x_sub,
				y * data->mini->mini_img_size + y_sub, colour);
			y_sub++;
		}
		x_sub++;
	}
}

void	draw_minimap(t_data *data, int y)
{
	int			x;
	uint32_t	colour;
	int			map_width;
	int			map_height;

	map_height = ft_strlen_double(data->map->map);
	while (y < map_height)
	{
		x = 0;
		map_width = ft_strlen(data->map->map[y]);
		while (x < map_width)
		{
			if (data->map->map[y][x] == '1')
				colour = MINI_WALL_COLOUR;
			else if (data->map->map[y][x] == '0'
				|| data->map->map[y][x] == data->player.position)
				colour = MINI_FLOOR_COLOUR;
			else
				colour = MINI_BASE_COLOUR;
			draw_mini_sub(data, colour, x, y);
			x++;
		}
		y++;
	}
	draw_player(data);
}
