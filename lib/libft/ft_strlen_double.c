/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narrospi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:07:16 by narrospi          #+#    #+#             */
/*   Updated: 2025/06/23 20:07:20 by narrospi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_double(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}
