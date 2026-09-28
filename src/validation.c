/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:05:50 by narrospi          #+#    #+#             */
/*   Updated: 2025/05/29 14:18:35 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_parameters(int ac, char **av, t_data *data)
{
	char	*extension;
	int		len_str;
	int		result;

	data->checker = 1;
	if (ac != 2)
		ft_error("Error. number of arguments incorrect\n", data);
	else
	{
		len_str = ft_strlen(av[1]);
		extension = ft_substr(av[1], len_str - 4, 4);
		result = ft_strncmp(extension, ".cub", 4);
		free(extension);
		if (result != 0)
			ft_error("Error. Incorrect extension (.cub)\n", data);
		extension = ft_substr(av[1], len_str - 5, 5);
		result = ft_strncmp(extension, "/.cub", 5);
		free(extension);
		if (result == 0)
			ft_error("Error. file without name\n", data);
	}
}
