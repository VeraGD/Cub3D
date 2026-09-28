/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:30:49 by narrospi          #+#    #+#             */
/*   Updated: 2025/06/21 13:30:51 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static uint32_t	get_colours(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	uint32_t	*pixel;

	if (!texture || x >= texture->width || y >= texture->height)
		return (0);
	pixel = (uint32_t *)texture->pixels;
	return (pixel[y * texture->width + x]);
}

void	colouring(mlx_image_t *image, uint32_t x, \
	uint32_t y, uint32_t colour)
{
	uint32_t	*pixel;

	if (!image || x >= image->width || y >= image->height)
		return ;
	pixel = (uint32_t *)image->pixels;
	pixel[y * image->width + x] = colour;
}

static void	view_in(t_data *data)
{
	uint32_t	i;
	double		ratio;
	uint32_t	start_draw;
	uint32_t	tex_y ;
	uint32_t	colour;

	ratio = (double)data->rayc.hit_text->height / data->rayc.slice_height;
	start_draw = (data->rayc.slice_height - data->image->height) / 2;
	i = 0;
	while (i < data->image->height)
	{
		tex_y = (start_draw + i) * ratio;
		if (tex_y >= data->rayc.hit_text->height)
			tex_y = data->rayc.hit_text->height - 1;
		colour = get_colours(data->rayc.hit_text, data->rayc.texture_x, tex_y);
		colouring(data->image, data->rayc.slice, i++, colour);
	}
}

static void	view_out(t_data *data)
{
	uint32_t	rest;
	double		ratio;
	uint32_t	i;
	uint32_t	tex_y;
	uint32_t	colour;

	rest = (data->image->height - data->rayc.slice_height) / 2;
	ratio = (double)data->rayc.hit_text->height / data->rayc.slice_height;
	i = 0;
	while (i < rest)
		colouring(data->image, data->rayc.slice, i++, data->map->c);
	while (i < data->image->height - rest)
	{
		tex_y = (i - rest) * ratio;
		if (tex_y >= data->rayc.hit_text->height)
			tex_y = data->rayc.hit_text->height - 1;
		colour = get_colours(data->rayc.hit_text, data->rayc.texture_x, tex_y);
		colouring(data->image, data->rayc.slice, i++, colour);
	}
	while (i < data->image->height)
		colouring(data->image, data->rayc.slice, i++, data->map->f);
}

void	draw_slice(t_data *data)
{
	double	correct_dist;

	correct_dist = data->rayc.wall_dist[data->rayc.slice] * \
		cos(atan(data->rayc.shift_factor));
	data->rayc.slice_height = (uint32_t)(data->image->height / correct_dist);
	data->rayc.texture_x = data->rayc.hit_text->width * data->rayc.hit_portion;
	if (data->rayc.slice_height > data->image->height)
		view_in(data);
	else
		view_out(data);
}
