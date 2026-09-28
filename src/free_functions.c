/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:19:27 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/29 14:20:37 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_charge_images(char **s)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (s[i] != NULL)
			free(s[i]);
		i++;
	}
	free(s);
}

void	free_textures(t_data *data)
{
	if (data->north)
		mlx_delete_texture(data->north);
	if (data->south)
		mlx_delete_texture(data->south);
	if (data->west)
		mlx_delete_texture(data->west);
	if (data->east)
		mlx_delete_texture(data->east);
}

void	free_structs(t_map *map, t_data *data)
{
	if (map->map)
		free_split(map->map);
	if (map)
		free(map);
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	free_textures(data);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data->img_charge)
		free_charge_images(data->img_charge);
	if (data)
		free(data);
}
