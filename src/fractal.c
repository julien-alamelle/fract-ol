/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:43:29 by jalamell          #+#    #+#             */
/*   Updated: 2022/05/31 18:38:42 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "fractol.h"

//	z -= (zz + 1)(z - c)/(3zz - 2zc + 1)
static int	newton(t_cpx z, t_cpx c, t_data *data)
{
	int		i;
	t_cpx	num;
	t_cpx	den;

	i = -1;
	while (++i < data->depth)
	{
		num = cpx_mlt(cpx_add(cpx_mlt(z, z), cpx(1., 0.)),
				cpx_add(z, cpx_neg(c)));
		den = cpx_add(cpx_mlt(cpx(3., 0.), cpx_mlt(z, z)),
				cpx_add(cpx_mlt(cpx(-2., 0.), cpx_mlt(z, c)), cpx(1., 0.)));
		z = cpx_add(z, cpx_neg(cpx_mlt(num, cpx_inv(den))));
		if (hypot(z.r, z.i - 1.) < .0001)
			return (simple_hsl_to_rgb(0.666666));
		if (hypot(z.r, z.i + 1.) < .0001)
			return (simple_hsl_to_rgb(0.333333));
		if (hypot(z.r - c.r, z.i - c.i) < .0001)
			return (simple_hsl_to_rgb(0.));
	}
	return (0);
}

static int	julia_loop(t_cpx z, t_cpx c, double er, t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->depth && hypot(z.r, z.i) < er)
		z = cpx_add(cpx_mlt(z, z), c);
	if (hypot(z.r, z.i) < er)
		return (0);
	return (simple_hsl_to_rgb((double) i / data->color_nb));
}

static int	mandelbrot(t_cpx z, t_cpx c, t_data *data)
{
	double	tmp;

	if (hypot(c.r + 1., c.i) < 0.25)
		return (0);
	tmp = hypot(c.r - 0.25, c.i);
	if (tmp < 0.5 - (c.r / 2. - 0.125) / tmp)
		return (0);
	return (julia_loop(z, c, 2., data));
}

void	render(t_data *d)
{
	int			x;
	int			y;
	int			*img;
	t_cpx		p;
	const t_cpx	m = cpx(d->mouse_x, d->mouse_y);

	img = (int *) d->img;
	x = d->win_x;
	while (x--)
	{
		y = d->win_y;
		while (y--)
		{
			p = cpx(itod(d, x, 'x') + d->ox, itod(d, y, 'y') + d->oy);
			if (d->fractal == 1)
				img[(y * d->win_x + x)] = julia_loop(p, m, 2., d);
			if (d->fractal == 2)
				img[(y * d->win_x + x)] = mandelbrot(cpx(0., 0.), p, d);
			if (d->fractal == 3)
				img[(y * d->win_x + x)] = newton(p, m, d);
			if (d->fractal == 4)
				img[(y * d->win_x + x)] = newton(cpx(p.r / 3., p.i / 3.), p, d);
		}
	}
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img_ptr, 0, 0);
}
