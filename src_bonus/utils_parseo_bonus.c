/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parseo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:05:39 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/29 14:11:20 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

size_t	ft_strlen_double(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] && ft_strcmp(split[i], "\n"))
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	skip_spaces_simple(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\0'
			&& line[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	skip_spaces(char **split)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (split[i] != NULL)
			return (1);
		i++;
	}
	return (0);
}

size_t	max_len_split(char **split)
{
	int		i;
	size_t	len;

	len = 0;
	i = 0;
	while (split[i])
	{
		if (ft_strlen(split[i]) > len)
			len = ft_strlen(split[i]);
		i++;
	}
	return (len);
}
