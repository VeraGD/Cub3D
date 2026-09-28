/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing_gf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:26:27 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/29 14:31:37 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

mlx_texture_t	*load_texture(char *f, t_data *d)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(f);
	if (!texture)
		ft_error("Error loading PNG file\n", d);
	return (texture);
}

static int	put_image(char **split, t_data *data)
{
	char		*path;

	path = ft_strtrim(split[1], "\n");
	if (ft_strcmp(split[0], "NO") == 0)
		data->img_charge[0] = ft_strdup(path);
	else if (ft_strcmp(split[0], "SO") == 0)
		data->img_charge[1] = ft_strdup(path);
	else if (ft_strcmp(split[0], "WE") == 0)
		data->img_charge[2] = ft_strdup(path);
	else if (ft_strcmp(split[0], "EA") == 0)
		data->img_charge[3] = ft_strdup(path);
	else
	{
		free(path);
		free_split(split);
		ft_error("There is a repeated image\n", data);
	}
	free(path);
	return (1);
}

static int	is_valid_texture_name(char *name)
{
	if (ft_strcmp(name, "NO") == 0 || ft_strcmp(name, "SO") == 0
		|| ft_strcmp(name, "WE") == 0 || ft_strcmp(name, "EA") == 0)
		return (0);
	return (1);
}

int	search_textures(char *line, t_map *m, t_data *d, int cc)
{
	char	**split;
	int		c;

	c = 0;
	split = ft_split_double(line, ' ', '\t', 0);
	if (skip_spaces(split) == 0)
	{
		free_split(split);
		return (c);
	}
	if (is_valid_texture_name(split[0]) == 0)
		c = put_image(split, d);
	else if (ft_strcmp(split[0], "F") == 0 || ft_strcmp(split[0], "C") == 0)
		c = get_colors(split, m, d, 0);
	else if (skip_spaces_simple(line) == 1)
	{
		free(line);
		free_split(split);
		if (cc == 5)
			ft_error("Invalid/Missing map attribute\n", d);
		else
			ft_error("Map before attributes or wrong map attribute\n", d);
	}
	free_split(split);
	return (c);
}

void	charge_all_animations(char *path, t_data *data, mlx_texture_t **t)
{
	char	*path_name;
	char	*path_num;
	char	*path_to_charge;
	char	num[2];
	int		i;

	num[0] = '2';
	num[1] = '\0';
	i = 1;
	t[0] = load_texture(path, data);
	path_name = ft_substr(path, 0, ft_strlen(path) - 5);
	while (i < 7)
	{
		path_num = ft_strjoin(path_name, num);
		num[0]++;
		path_to_charge = ft_strjoin(path_num, ".png");
		t[i] = load_texture(path_to_charge, data);
		free(path_num);
		free(path_to_charge);
		i++;
	}
	free(path_name);
}
