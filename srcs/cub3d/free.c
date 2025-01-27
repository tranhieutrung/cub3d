/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:51:23 by ktieu             #+#    #+#             */
/*   Updated: 2025/01/27 09:14:02 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d_free(t_cub3d *c)
{
	if (c)
	{
		am_free(c->mlx, &c->am);
		clean_elems(c->element);
		clean_map(c->map);
	}
}