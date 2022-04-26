/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 17:54:29 by jalamell          #+#    #+#             */
/*   Updated: 2022/04/26 18:50:50 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
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

static void	ft_strjoin_size(char **str1, int *size1, char *str2, int size2)
{
	int		i;
	char	*ret;

	i = *size1;
	*size1 = size2 + i;
	ret = malloc(*size1 + 1);
	ret[*size1] = 0;
	while (size2--)
		ret[i + size2] = str2[size2];
	while (i--)
		ret[i] = (*str1)[i];
	free(*str1);
	*str1 = ret;
}

static int	getfile(char **ret, int size, char *file)
{
	int		fd;
	char	buff[1024];
	int		i;

	fd = open(file, O_RDONLY);
	i = read(fd, buff, 1024);
	while (i)
	{
		ft_strjoin_size(ret, &size, buff, i);
		i = read(fd, buff, 1024);
	}
	close(fd);
	return (size);
}

static void	cl_init(t_opencl *cl, int size)
{
	cl_int			err;
	cl_platform_id	platf;
	cl_device_id	dev;

	cl->src = malloc(1);
	cl->src[0] = 0;
	cl->t_size = size;
	cl->g_size = 64;
	getfile(&cl->src, 0, "src/multi.cl");
	err = clGetPlatformIDs(1, &platf, NULL);
	err = clGetDeviceIDs(platf, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
	cl->context = clCreateContext(NULL, 1, &dev, NULL, NULL, &err);
	cl->prog = clCreateProgramWithSource(cl->context, 1,
			(const char **)&cl->src, NULL, &err);
	err = clBuildProgram(cl->prog, 1, &dev, NULL, NULL, NULL);
	cl->img = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY,
			cl->t_size * sizeof(int), NULL, &err);
	cl->command = clCreateCommandQueue(cl->context, dev, 0, &err);
	cl->kernel = clCreateKernel(cl->prog, "fractal_calc", &err);
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
	data->cl = malloc(sizeof(t_opencl));
	cl_init(data->cl, data->win_x * data->win_y);
}
