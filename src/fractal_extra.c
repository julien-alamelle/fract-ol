/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:43:29 by jalamell          #+#    #+#             */
/*   Updated: 2022/05/27 15:50:53 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "fractol_extra.h"

void	render(t_data *data)
{
	cl_int	er;

	er = clSetKernelArg(data->cl_kernel, 0, sizeof(cl_mem), &(data->cl_img));
	er = clSetKernelArg(data->cl_kernel, 1, sizeof(int), &(data->fractal));
	er = clSetKernelArg(data->cl_kernel, 2, sizeof(int), &(data->win_x));
	er = clSetKernelArg(data->cl_kernel, 3, sizeof(int), &(data->win_y));
	er = clSetKernelArg(data->cl_kernel, 4, sizeof(double), &(data->ox));
	er = clSetKernelArg(data->cl_kernel, 5, sizeof(double), &(data->oy));
	er = clSetKernelArg(data->cl_kernel, 6, sizeof(double), &(data->zoom));
	er = clSetKernelArg(data->cl_kernel, 7, sizeof(double), &(data->mouse_x));
	er = clSetKernelArg(data->cl_kernel, 8, sizeof(double), &(data->mouse_y));
	er = clSetKernelArg(data->cl_kernel, 9, sizeof(double), &(data->er));
	er = clSetKernelArg(data->cl_kernel, 10, sizeof(int), &(data->depth));
	er = clSetKernelArg(data->cl_kernel, 11, 8, &(data->color_nb));
	er = clEnqueueNDRangeKernel(data->cl_command, data->cl_kernel, 1, NULL,
			&(data->cl_t_size), &(data->cl_g_size), 0, NULL, NULL);
	er = clEnqueueReadBuffer(data->cl_command, data->cl_img, CL_TRUE, 0,
			data->cl_t_size * sizeof(int), data->img, 0, NULL, NULL);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img_ptr, 0, 0);
	clFlush(data->cl_command);
}
