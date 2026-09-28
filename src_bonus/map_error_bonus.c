/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:20:55 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/29 16:33:36 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	check_start_point(char *map, int c, t_data *data)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != '0' && map[i] != '1' && map[i] != '\n' && map[i] != ' ')
		{
			if (map[i] == 'N')
				data->player.position = 'N';
			else if (map[i] == 'S')
				data->player.position = 'S';
			else if (map[i] == 'E')
				data->player.position = 'E';
			else if (map[i] == 'W')
				data->player.position = 'W';
			else
			{
				free(map);
				ft_error("Invalid character in the map\n", data);
			}
			c++;
		}
		i++;
	}
	return (c);
}

void	check_characters(char *map, t_data *data)
{
	int	c;

	c = 0;
	c = check_start_point(map, c, data);
	if (c < 1)
	{
		free(map);
		ft_error("No start point in the map\n", data);
	}
	else if (c > 1)
	{
		free(map);
		ft_error("More than one start point in the map\n", data);
	}
}

char	**fill_spaces(char **split, t_data *data)
{
	size_t	len;
	int		i;
	char	*new;
	char	*spaces;

	len = max_len_split(split);
	i = 0;
	while (split[i])
	{
		if (ft_strlen(split[i]) < len)
		{
			new = malloc((len - ft_strlen(split[i]) + 2) * sizeof(char));
			if (!new)
				ft_error("Error allocating memory", data);
			ft_memset(new, ' ', len - ft_strlen(split[i]));
			new[len - ft_strlen(split[i])] = '\0';
			spaces = ft_strjoin(split[i], new);
			free(new);
			free(split[i]);
			split[i] = spaces;
		}
		i++;
	}
	return (split);
}

static void	check_ones_spaces(char **s, size_t i, t_data *data)
{
	size_t	j;
	size_t	height;

	j = 0;
	height = ft_strlen_double(s);
	while (j < ft_strlen(s[i]))
	{
		if (s[i][j] == ' ')
		{
			if (i > 0 && j < ft_strlen(s[i - 1])
				&& s[i - 1][j] != ' ' && s[i - 1][j] != '1')
				ft_error("Walls are not surrounded by 1\n", data);
			if (i + 1 < height && j < ft_strlen(s[i + 1])
				&& s[i + 1][j] != ' ' && s[i + 1][j] != '1')
				ft_error("Walls are not surrounded by 1\n", data);
			if (j > 0
				&& s[i][j - 1] != ' ' && s[i][j - 1] != '1')
				ft_error("Walls are not surrounded by 1\n", data);
			if (j + 1 < ft_strlen(s[i])
				&& s[i][j + 1] != ' ' && s[i][j + 1] != '1')
				ft_error("Walls are not surrounded by 1\n", data);
		}
		j++;
	}
}

void	check_ones(char **s, t_data *data)
{
	size_t	i;
	size_t	height;

	i = 0;
	height = ft_strlen_double(s);
	while (i < height)
	{
		check_ones_spaces(s, i, data);
		i++;
	}
}
