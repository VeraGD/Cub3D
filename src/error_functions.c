/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:55:08 by veragarc          #+#    #+#             */
/*   Updated: 2025/05/29 13:55:23 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_error(char *str, t_data *data)
{
	if (data->checker == 1)
		free(data);
	else
		free_structs(data->map, data);
	ft_putstr_fd(str, 1);
	exit(1);
}
