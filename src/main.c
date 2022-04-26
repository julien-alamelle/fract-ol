/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:18:30 by jalamell          #+#    #+#             */
/*   Updated: 2022/04/26 18:51:17 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>			/*TODO*/
#include <stdlib.h>
#include "fractol.h"
#include <math.h>

void	render_test(t_data *data)
{
	int		x;
	int		y;
	int		*img;

	img = (int *) data->img;
	x = data->win_x;
	while (x--)
	{
		y = data->win_y;
		while (y--)
			img[(y * data->win_x + x)] = mandelbrot(data, x, y);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img_ptr, 0, 0);
}

void	render(t_data *data)
{
	cl_int	er;

	er = clSetKernelArg(data->cl->kernel, 0, sizeof(cl_mem), &(data->cl->img));
	er = clSetKernelArg(data->cl->kernel, 1, sizeof(int), &(data->fractal));
	er = clSetKernelArg(data->cl->kernel, 2, sizeof(int), &(data->win_x));
	er = clSetKernelArg(data->cl->kernel, 3, sizeof(int), &(data->win_y));
	er = clSetKernelArg(data->cl->kernel, 4, sizeof(double), &(data->ox));
	er = clSetKernelArg(data->cl->kernel, 5, sizeof(double), &(data->oy));
	er = clSetKernelArg(data->cl->kernel, 6, sizeof(double), &(data->zoom));
	er = clSetKernelArg(data->cl->kernel, 7, sizeof(double), &(data->mouse_x));
	er = clSetKernelArg(data->cl->kernel, 8, sizeof(double), &(data->mouse_y));
	er = clSetKernelArg(data->cl->kernel, 9, sizeof(double), &(data->er));
	er = clSetKernelArg(data->cl->kernel, 10, sizeof(int), &(data->depth));
	er = clSetKernelArg(data->cl->kernel, 11, 8, &(data->color_nb));
	er = clEnqueueNDRangeKernel(data->cl->command, data->cl->kernel, 1, NULL,
			&(data->cl->t_size), &(data->cl->g_size), 0, NULL, NULL);
	er = clEnqueueReadBuffer(data->cl->command, data->cl->img, CL_TRUE, 0,
			data->cl->t_size * sizeof(int), data->img, 0, NULL, NULL);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img_ptr, 0, 0);
	clFlush(data->cl->command);
}

int	ft_exit(void *param)
{
	t_data *const	data = param;

	if (data->cl)
	{
		clFlush(data->cl->command);
		clFinish(data->cl->command);
		clReleaseKernel(data->cl->kernel);
		clReleaseProgram(data->cl->prog);
		clReleaseMemObject(data->cl->img);
		clReleaseCommandQueue(data->cl->command);
		clReleaseContext(data->cl->context);
		free(data->cl->src);
		free(data->cl);
	}
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	data_init(&data);
	if (data_add_input(&data, ac - 1, av + 1))
		exit(0);
	render(&data);
	mlx_hook(data.win_ptr, 17, 0, ft_exit, &data);
	mlx_hook(data.win_ptr, 2, 0, ft_key_hook, &data);
	mlx_hook(data.win_ptr, 4, 0, ft_mouse_hook, &data);
	mlx_hook(data.win_ptr, 6, 0, ft_move_hook, &data);
	mlx_loop(data.mlx_ptr);
}
