/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:59:06 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/29 14:05:24 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static char	*map_textures(t_map *map, t_data *data, int fd)
{
	char	*line;
	int		c;

	c = 0;
	line = get_next_line(fd);
	if (line == NULL)
	{
		free(line);
		ft_error("Empty map\n", data);
	}
	while (line != NULL)
	{
		c += search_textures(line, map, data, c);
		free(line);
		line = get_next_line(fd);
		if (c == 6)
			break ;
	}
	if (line == NULL)
	{
		free(line);
		ft_error("There is not map in the filee\n", data);
	}
	return (line);
}

static char	*get_map(char *line, int fd, t_data *d)
{
	char	*res;
	char	*temp;

	res = ft_strdup(line);
	free(line);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (skip_spaces_simple(line) == 0)
		{
			free(res);
			free(line);
			ft_error("Empty line in map or repeated/wrong attribute\n", d);
		}
		temp = ft_strjoin(res, line);
		free(res);
		res = ft_strdup(temp);
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (res);
}

static char	*return_map(char *line, int fd, t_data *d)
{
	char	*res;
	size_t	len;

	while (skip_spaces_simple(line) == 0)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
		{
			free(line);
			ft_error("There is not map in the file\n", d);
		}
	}
	res = get_map(line, fd, d);
	len = ft_strlen(res) - 1;
	if (res[len] == '\n')
		ft_error("There is a new line after the map\n", d);
	return (res);
}

static void	check_ends_map(char **s, t_data *d)
{
	size_t	i;
	size_t	h;
	size_t	l;
	size_t	j;

	i = 0;
	h = ft_strlen_double(s) - 1;
	l = ft_strlen(s[0]) - 1;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (i == 0 && (s[i][j] != '1' && s[i][j] != ' '))
				ft_error("Walls are not surrounded by 1\n", d);
			else if (j == 0 && (s[i][j] != '1' && s[i][j] != ' '))
				ft_error("Walls are not surrounded by 1\n", d);
			if (i == h && (s[i][j] != '1' && s[i][j] != ' '))
				ft_error("Walls are not surrounded by 1\n", d);
			else if (j == l && (s[i][j] != '1' && s[i][j] != ' '))
				ft_error("Walls are not surrounded by 1\n", d);
			j++;
		}
		i++;
	}
}

void	map_parsing(char *path, t_map *map, t_data *data)
{
	char	*line;
	char	*res;
	char	**split;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error("Error opening file", data);
	line = map_textures(map, data, fd);
	res = return_map(line, fd, data);
	check_characters(res, data);
	split = ft_split(res, '\n');
	split = fill_spaces(split, data);
	check_ones(split, data);
	check_ends_map(split, data);
	map->map = split;
	charge_all_animations(data->img_charge[0], data, data->north);
	charge_all_animations(data->img_charge[1], data, data->south);
	charge_all_animations(data->img_charge[2], data, data->west);
	charge_all_animations(data->img_charge[3], data, data->east);
	free(res);
}
