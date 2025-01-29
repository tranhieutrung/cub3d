/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:17:25 by hitran            #+#    #+#             */
/*   Updated: 2025/01/29 10:39:40 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	check_elem_type(char *line)
{
	if (!ft_strcmp(line, "NO"))
		return (NO);
	else if (!ft_strcmp(line, "SO"))
		return (SO);
	else if (!ft_strcmp(line, "WE"))
		return (WE);
	else if (!ft_strcmp(line, "EA"))
		return (EA);
	else if (!ft_strcmp(line, "F"))
		return (F);
	else if (!ft_strcmp(line, "C"))
		return (C);
	else
		return (-1);
}

static int	parse_color(t_element *element, char **splitted_line, int elem_type)
{
	char	**array;

	array = ft_split(splitted_line[1], ',');
	if (!array)
		return (ft_error_ret("ft_split failed.", EXIT_FAILURE));
	if (ft_array_len(array) != 3
		|| splitted_line[1][ft_strlen(splitted_line[1]) - 1] == ',')
	{
		ft_clean_array(&array);
		return (ft_error_ret("Invalid color format.", EXIT_FAILURE));
	}
	if ((elem_type == F
			&& ft_set_color(&element->f_color, array) == EXIT_FAILURE)
		|| (elem_type == C
			&& ft_set_color(&element->c_color, array) == EXIT_FAILURE))
	{
		ft_clean_array(&array);
		return (EXIT_FAILURE);
	}
	ft_clean_array(&array);
	return (EXIT_SUCCESS);
}

static int	save_element(t_element *element, char	**splitted_line,
			int elem_type)
{
	int	fd;

	if (elem_type == F || elem_type == C)
		return (parse_color(element, splitted_line, elem_type));
	fd = ft_validate_elem_path(splitted_line[1]);
	if (fd < 0)
		return (EXIT_FAILURE);
	if (elem_type == NO)
		element->no_fd = fd;
	else if (elem_type == SO)
		element->so_fd = fd;
	else if (elem_type == WE)
		element->we_fd = fd;
	else if (elem_type == EA)
		element->ea_fd = fd;
	return (EXIT_SUCCESS);
}

static int	parse_element(t_element *element, char **splitted_line,
			int elem_type)
{
	if ((elem_type == NO && element->no_fd)
		|| (elem_type == SO && element->so_fd)
		|| (elem_type == WE && element->we_fd)
		|| (elem_type == EA && element->ea_fd)
		|| (elem_type == F && element->f_color)
		|| (elem_type == C && element->c_color))
	{
		ft_clean_array(&splitted_line);
		return (ft_error_ret("Elements duplicated.", EXIT_FAILURE));
	}
	if (save_element(element, splitted_line, elem_type) == EXIT_FAILURE)
	{
		ft_clean_array(&splitted_line);
		return (EXIT_FAILURE);
	}
	if (element->no_fd && element->so_fd && element->we_fd
		&& element->ea_fd && element->f_color && element->c_color)
		element->done = 1;
	ft_clean_array(&splitted_line);
	return (EXIT_SUCCESS);
}

int	read_element(t_element *element, char *line)
{
	char	**splitted_line;
	int		size;
	int		elem_type;

	if (!line[0])
		return (EXIT_SUCCESS);
	splitted_line = ft_split(line, ' ');
	if (!splitted_line)
		return (ft_error_ret("ft_split failed.", EXIT_FAILURE));
	size = ft_array_len(splitted_line);
	if (size != 2)
	{
		ft_clean_array(&splitted_line);
		return (ft_error_ret("Invalid element format.", EXIT_FAILURE));
	}
	elem_type = check_elem_type(splitted_line[0]);
	if (elem_type == -1)
	{
		ft_clean_array(&splitted_line);
		return (ft_error_ret("Invalid element types.", EXIT_FAILURE));
	}
	return (parse_element(element, splitted_line, elem_type));
}
