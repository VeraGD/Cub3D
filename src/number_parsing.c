/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:14:14 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/29 14:18:06 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_comas(char *s, t_data *data)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == ',')
			c++;
		i++;
	}
	if (c != 2)
		ft_error("Invalid comas in color number\n", data);
}

// el trim es por si meto espacios o tabuladores o demas despues del numero 
// y no me entero
static char	**check_nums(char **split, int i, t_data *data)
{
	char	**nums;
	char	*tmp;

	if (ft_strlen_double(split) != 2)
	{
		free_split(split);
		ft_error("Invalid color number format\n", data);
	}
	nums = ft_split(split[1], ',');
	if (ft_strlen_double(nums) != (size_t)3)
	{
		free_split(nums);
		free_split(split);
		ft_error("Invalid color number format\n", data);
	}
	check_comas(split[1], data);
	while (i < 3)
	{
		tmp = nums[i];
		nums[i] = ft_strtrim(tmp, " \n\t");
		free(tmp);
		i++;
	}
	return (nums);
}

static void	set_nums(char **split, int *res, t_map *map, t_data *data)
{
	if (ft_strcmp(split[0], "F") == 0 && map->f == UINT32_MAX)
		map->f = (255 << 24) | (res[2] << 16) | (res[1] << 8) | res[0];
	else if (ft_strcmp(split[0], "C") == 0 && map->c == UINT32_MAX)
		map->c = (255 << 24) | (res[2] << 16) | (res[1] << 8) | res[0];
	else
	{
		free_split(split);
		free(res);
		ft_error("There is a repeated color\n", data);
	}
	free(res);
}

static int	is_valid_num(char *n)
{
	int	i;

	i = 0;
	while (n[i])
	{
		if (n[i] < '0' || n[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	get_colors(char **split, t_map *m, t_data *d, int i)
{
	int		num;
	int		*res;
	char	**nums;

	nums = check_nums(split, 0, d);
	res = (int *)malloc(3 * sizeof(int));
	if (!res)
		ft_error("Error allocating memory", d);
	while (nums[i])
	{
		num = ft_atoi(nums[i]);
		if (num < 0 || num > 255 || is_valid_num(nums[i]) == 1)
		{
			free_split(split);
			free_split(nums);
			ft_error("Invalid format for color number [0 - 255]\n", d);
		}
		else
			res[i] = num;
		i++;
	}
	free_split(nums);
	set_nums(split, res, m, d);
	return (1);
}
