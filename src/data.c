/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:54:29 by jalamell          #+#    #+#             */
/*   Updated: 2022/05/31 18:12:36 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// for fulscreen x = 2560, y = 1395

double	itod(t_data *data, int coord, char axis)
{
	int	size;
	int	sign;

	size = data->win_x;
	sign = 1;
	if (axis == 'y')
		sign = -1;
	if (axis == 'y')
		size = data->win_y;
	return (((double)(2 * coord - size)) * data->zoom * sign);
}

void	data_init(t_data *data)
{
	data->win_x = 512;
	data->win_y = 512;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_x,
			data->win_y, "fract'ol");
	data->img_ptr = mlx_new_image(data->mlx_ptr, data->win_x, data->win_y);
	data->img = mlx_get_data_addr(data->img_ptr, &data->bpp,
			&data->size_line, &data->endian);
	data->ox = -0.;
	data->oy = 0.;
	data->zoom = 2. / data->win_x;
	data->depth = 50;
	data->color_nb = 20.;
	data->fractal = 2;
	data->mouse_lock = 0;
	data->mouse_x = 0.;
	data->mouse_y = 0.;
	data->er = 2.;
}

void	data_del(t_data *data)
{
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
}
