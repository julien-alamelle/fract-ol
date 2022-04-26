/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:59:22 by jalamell          #+#    #+#             */
/*   Updated: 2022/04/26 18:51:21 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_STRUCT_H
# define FRACTOL_STRUCT_H

# include <OpenCL/opencl.h>

typedef struct s_opencl
{
	unsigned long		t_size;
	unsigned long		g_size;
	cl_mem				img;
	cl_command_queue	command;
	cl_kernel			kernel;
	cl_program			prog;
	cl_context			context;
	char				*src;
}	t_opencl;

typedef struct s_cpx
{
	double	r;
	double	i;
}	t_cpx;

typedef struct s_data
{
	int			win_x;
	int			win_y;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img;
	int			bpp;
	int			size_line;
	int			endian;
	double		ox;
	double		oy;
	double		zoom;
	int			depth;
	double		color_nb;
	int			fractal;
	int			mouse_lock;
	double		mouse_x;
	double		mouse_y;
	double		er;
	t_opencl	*cl;
}	t_data;

void	data_init(t_data *data);
t_cpx	cpx(double r, double i);
t_cpx	cpx_add(t_cpx cpx1, t_cpx cpx2);
t_cpx	cpx_mlt(t_cpx cpx1, t_cpx cpx2);
t_cpx	cpm_neg(t_cpx cpx);
t_cpx	cpx_inv(t_cpx cpx);

#endif
