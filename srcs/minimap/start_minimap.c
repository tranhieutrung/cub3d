// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   start_cub.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/20 00:30:53 by hitran            #+#    #+#             */
// /*   Updated: 2025/01/29 11:00:00 by hitran           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "cub3d.h"

static void	update_beams(t_cub *cub)
{
	mlx_delete_image(cub->mlx, cub->mini[RAY]);
	cub->mini[RAY] = png_to_ray(cub, M_RAY);
	draw_rays(cub);
}

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub		*cub;
	double		angle;
	// t_dpoint	cur;

	cub = (t_cub *)param;
	// cur = cub->player.current;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit_cub(cub, EXIT_SUCCESS);
	// else if (keydata.key == MLX_KEY_W)
	// 	cub->player.next.y = cur.y - 4;
	// else if (keydata.key == MLX_KEY_S)
	// 	cub->player.next.y = cur.y + 4;
	// else if (keydata.key == MLX_KEY_A)
	// 	cub->player.next = (t_point){cur.x - 1, cur.y, cur.rad};
	// else if (keydata.key == MLX_KEY_D)
	// 		cub->player.next = (t_point){cur.x + 1, cur.y, cur.rad};
	else if (keydata.key == MLX_KEY_LEFT)
		cub->player.angle = rescale(cub->player.angle + PI / 36);
	else if (keydata.key == MLX_KEY_RIGHT)
		cub->player.angle = rescale(cub->player.angle - PI / 36);
	else
		return ;
	update_beams(cub);
	// cub->player.angle = angle;
	// if (cub->map.grid[cub->player.next.y][cub->player.next.x] != '1')
	// 	move_player(cub);
}

static void	loop_hook(void *param)
{
	t_cub		*cub;

	cub = (t_cub *)param;
	// mlx_key_hook(cub->mlx, key_hook, cub);
	ray_casting(cub);
}

static void	close_hook(void *param)
{
	exit_cub((t_cub *)param, EXIT_SUCCESS);
}

void	init_hooks(t_cub *cub)
{
	if (mlx_loop_hook(cub->mlx, loop_hook, cub) == false)
		game_error(cub, strerror(errno));
	mlx_close_hook(cub->mlx, close_hook, cub);
}

void	start_minimap(t_cub *cub)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub->mlx = mlx_init(WIDTH, HEIGHT, "minimap", true);
	if (!cub->mlx)
		game_error(cub, mlx_strerror(mlx_errno));

	// cub->rays = (t_ray *)ft_calloc(WIDTH, sizeof(t_ray));
	cub->rays = (t_ray *)ft_calloc(19, sizeof(t_ray)); //5 degree * 18 = 90
	if (cub->rays == NULL)
		game_error(cub, strerror(errno));

	display_minimap(cub, -1, -1);
	ray_casting(cub);
	draw_rays(cub);
	mlx_key_hook(cub->mlx, key_hook, cub);
	mlx_loop_hook(cub->mlx, loop_hook, cub);
	mlx_close_hook(cub->mlx, close_hook, cub);
	mlx_loop(cub->mlx);
	exit_cub(cub, EXIT_SUCCESS);
}
