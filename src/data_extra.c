/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:37:57 by jalamell          #+#    #+#             */
/*   Updated: 2022/05/27 16:06:10 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_extra.h"
#include "mlx.h"

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

static int	getfile(char **ret, int size, char *file)
{
	int		fd;
	char	buff[1024];
	int		i;
	int		j;
	char	*tmp;

	fd = open(file, O_RDONLY);
	i = read(fd, buff, 1024);
	while (i)
	{
		j = size;
		size = i + j;
		tmp = malloc(size + 1);
		tmp[size] = 0;
		while (i--)
			tmp[j + i] = buff[i];
		while (j--)
			tmp[j] = (*ret)[j];
		free(*ret);
		*ret = tmp;
		i = read(fd, buff, 1024);
	}
	close(fd);
	return (size);
}

static void	cl_init(t_data *data, int size)
{
	cl_int			err;
	cl_platform_id	platf;
	cl_device_id	dev;

	data->cl_src = malloc(1);
	data->cl_src[0] = 0;
	data->cl_t_size = size;
	data->cl_g_size = 64;
	getfile(&data->cl_src, 0, "src/multi.cl");
	err = clGetPlatformIDs(1, &platf, NULL);
	err = clGetDeviceIDs(platf, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
	data->cl_context = clCreateContext(NULL, 1, &dev, NULL, NULL, &err);
	data->cl_prog = clCreateProgramWithSource(data->cl_context, 1,
			(const char **)&data->cl_src, NULL, &err);
	err = clBuildProgram(data->cl_prog, 1, &dev, NULL, NULL, NULL);
	data->cl_img = clCreateBuffer(data->cl_context, CL_MEM_WRITE_ONLY,
			data->cl_t_size * sizeof(int), NULL, &err);
	data->cl_command = clCreateCommandQueue(data->cl_context, dev, 0, &err);
	data->cl_kernel = clCreateKernel(data->cl_prog, "fractal_calc", &err);
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
	cl_init(data, data->win_x * data->win_y);
}

void	data_del(t_data *data)
{
	clFlush(data->cl_command);
	clFinish(data->cl_command);
	clReleaseKernel(data->cl_kernel);
	clReleaseProgram(data->cl_prog);
	clReleaseMemObject(data->cl_img);
	clReleaseCommandQueue(data->cl_command);
	clReleaseContext(data->cl_context);
	free(data->cl_src);
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
}
