/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loop_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:32:20 by ktieu             #+#    #+#             */
/*   Updated: 2025/02/19 23:48:09 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_beams(t_cub *cub)
{
	mlx_delete_image(cub->mlx, cub->am.m_ray);
	cub->am.m_ray = am_load_png_ray(cub, M_RAY);
	draw_rays(cub);
}


static t_dpoint	next_point(t_dpoint cur, double angle, keys_t key)
{
	t_dpoint	next;

	next = (t_dpoint){cur.x, cur.y};
	if (key == MLX_KEY_W)
	{
		next = (t_dpoint){cur.x + cos(angle), cur.y - sin(angle)};
	}
	else if (key == MLX_KEY_S)
		next = (t_dpoint){cur.x - cos(angle), cur.y + sin(angle)};
	else if (key == MLX_KEY_A)
		next = (t_dpoint){cur.x + cos(angle + PI / 2),
							cur.y - sin(angle + PI / 2)};
	else if (key == MLX_KEY_D)
		next = (t_dpoint){cur.x + cos(angle + 3 * PI / 2),
							cur.y - sin(angle + 3 * PI / 2)};
	return (next);
}

static void process_key(t_cub *c)
{
	t_dpoint	cur;

	cur = c->player.current;
	c->player.prev =  c->player.current;
	if (mlx_is_key_down(c->mlx, MLX_KEY_ESCAPE))
		cub3d_exit(c, EXIT_SUCCESS);
	if (mlx_is_key_down(c->mlx, MLX_KEY_W))
	{
		c->player.current = next_point(cur, c->player.angle, MLX_KEY_W);
	}
	if (mlx_is_key_down(c->mlx, MLX_KEY_S))
		c->player.current = next_point(cur, c->player.angle, MLX_KEY_S);
	if (mlx_is_key_down(c->mlx, MLX_KEY_A))
		c->player.current = next_point(cur, c->player.angle, MLX_KEY_A);
	if (mlx_is_key_down(c->mlx, MLX_KEY_D))
		c->player.current = next_point(cur, c->player.angle, MLX_KEY_D);
	
	if (mlx_is_key_down(c->mlx, MLX_KEY_LEFT))
		c->player.angle = rescale(c->player.angle + PI / 36);
	if (mlx_is_key_down(c->mlx, MLX_KEY_RIGHT))
		c->player.angle = rescale(c->player.angle - PI / 36);
	// update_beams(c);
}

static void process_inputs(t_cub *c)
{
    process_key(c);
}

void	event_loop_handler(void *data)
{
	t_cub	*c;

	c = (t_cub *)data;
	process_inputs(c);
	correct_pos(c);
    draw_map(c);
	draw_minimap(c);
}

