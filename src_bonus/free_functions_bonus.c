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

#include "../includes/cub3d_bonus.h"

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

static void	free_charge_images(char **s)
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

static void	free_textures_double(mlx_texture_t **t)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (t[i])
			mlx_delete_texture(t[i]);
		i++;
	}
	free(t);
}

static void	free_textures(t_data *data)
{
	int	i;

	if (data->north)
		free_textures_double(data->north);
	if (data->south)
		free_textures_double(data->south);
	if (data->west)
		free_textures_double(data->west);
	if (data->east)
		free_textures_double(data->east);
	if (data->wand_img)
	{
		i = 0;
		while (i < 4)
		{
			if (data->wand_img[i])
				mlx_delete_image(data->mlx, data->wand_img[i]);
			i++;
		}
		free(data->wand_img);
	}
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
	if (data->mini)
		free(data->mini);
	if (data)
		free(data);
}
