/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:11:48 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/29 14:13:53 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

t_map	*ini_map(t_data *data)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_error("Error allocating memory", data);
	map->f = UINT32_MAX;
	map->c = UINT32_MAX;
	map->map = NULL;
	return (map);
}

static void	ini_animations(t_data *data)
{
	int	i;

	data->frame_count = 0;
	data->torch_frame = 0;
	data->north = malloc(8 * sizeof(mlx_texture_t));
	if (!data->north)
		ft_error("Error allocating memory for data structure", data);
	data->south = malloc(8 * sizeof(mlx_texture_t));
	if (!data->south)
		ft_error("Error allocating memory for data structure", data);
	data->east = malloc(8 * sizeof(mlx_texture_t));
	if (!data->east)
		ft_error("Error allocating memory for data structure", data);
	data->west = malloc(8 * sizeof(mlx_texture_t));
	if (!data->west)
		ft_error("Error allocating memory for data structure", data);
	i = 0;
	while (i < 8)
	{
		data->north[i] = NULL;
		data->south[i] = NULL;
		data->east[i] = NULL;
		data->west[i] = NULL;
		i++;
	}
}

void	ini_imgs(t_data *data)
{
	int	i;

	ft_memset(data, 0, sizeof(t_data));
	data->mlx = mlx_init(WIDTH, HEIGHT, "Expecto Raycastum", true);
	if (!data->mlx)
		ft_error("Error when initialising mlx", data);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
		ft_error("Error when creating image", data);
	data->fov_projection = 0.625;
	data->shift_distance = 2.0 * data->fov_projection / \
		(data->image->width -1.0);
	data->img_charge = (char **)malloc(5 * sizeof(char *));
	if (!data->img_charge)
		ft_error("Error allocating memory", data);
	i = 0;
	while (i < 5)
	{
		data->img_charge[i] = NULL;
		i++;
	}
	ini_animations(data);
	data->wand_frame = 0;
	data->wand_frame_count = 0;
	data->index = 0;
}
