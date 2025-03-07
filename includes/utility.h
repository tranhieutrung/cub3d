/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:37:09 by ktieu             #+#    #+#             */
/*   Updated: 2025/03/04 15:46:45 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

# ifndef GRID_BUFFER
#  define GRID_BUFFER 1000
# endif 

# include "MLX42.h"
# include "libft.h"
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "fcntl.h"

typedef struct s_cub	t_cub;

typedef struct s_color
{
	uint32_t	transparent;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
}	t_color;

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_point
{
	int	row;
	int	col;
}	t_point;

//----------------------------------------------
// ERROR
//----------------------------------------------
char		*ft_error_ret_null(char *str);
void		ft_error(char *str);
int			ft_error_ret(char *str, int return_code);
int			ft_multi_error_ret(char *str1, char *str2, int return_code);

//----------------------------------------------
// PATH
//----------------------------------------------
int			ft_validate_map_path(char *path);

//----------------------------------------------
// COLOR
//----------------------------------------------
int			ft_set_color(int *color, char **array);
int			ft_fill_color_int(mlx_image_t *img, int color);
int			ft_fill_color(mlx_image_t *img, t_color color);
uint32_t	ft_convert_color(t_color color);

//----------------------------------------------
// PIXELS
//----------------------------------------------
uint8_t		*ft_get_pixels(mlx_image_t *img, int32_t x, int32_t y);
int			ft_copy_pixels(
				mlx_image_t *dst,
				mlx_image_t *src,
				int32_t offset_x,
				int32_t offset_y);
void		ft_del_pixels(
				uint8_t *start_px,
				uint32_t img_width,
				int32_t offset_x,
				int32_t offset_y);
void		ft_destroy_img(t_cub *c, mlx_image_t **imgs);
int			ft_is_valid_pos(t_cub *c, int32_t x, int32_t y);

//----------------------------------------------
// UTILITY
//----------------------------------------------
char		*ft_readline(int fd, int *eof);
int			ft_is_all_white_spaces(char *s);
int			ft_array_len(char **array);
void		ft_clean_array(char ***str);
int			ft_max(int a, int b);

#endif
