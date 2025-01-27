/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:40:47 by hitran            #+#    #+#             */
/*   Updated: 2025/01/27 09:41:12 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

int	get_color(const char *str)
{
	int	number;

	if (!str[0] || ft_strlen(str) > 3)
		return (-1);
	number = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		number = number * 10 + *str++ - '0';
	}
	if (number > 255)
		return (-1);
	return (number);
}

int	ft_set_color(t_color *color, char **array)
{
	color->red = get_color(array[0]);
	color->green = get_color(array[1]);
	color->blue = get_color(array[2]);
	if (color->red == -1 || color->green == -1 || color->blue == -1)
		return (ft_error_ret("Invalid color format.", EXIT_FAILURE));
	color->done = 1;
	return (EXIT_SUCCESS);
}
