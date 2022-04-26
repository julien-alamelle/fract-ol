/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:43:29 by jalamell          #+#    #+#             */
/*   Updated: 2022/04/21 15:59:06 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fractol.h"

int	julia_loop(t_cpx z, t_cpx c, double er, t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->depth && hypot(z.r, z.i) < er)
		z = cpx_add(cpx_mlt(z, z), c);
	if (hypot(z.r, z.i) < er)
		return (0);
	return (simple_hsl_to_rgb((double) i * M_PI * 2. / data->color_nb));
}

static int	fast_mandelbrot(t_cpx z, t_cpx c, t_data *data)
{
	double	tmp;

	if (hypot(c.r + 1., c.i) < 0.25)
		return (0);
	tmp = hypot(c.r - 0.25, c.i);
	if (tmp < 0.5 - (c.r / 2. - 0.125) / tmp)
		return (0);
	return (julia_loop(z, c, 2., data));
}

int	mandelbrot(t_data *data, int ix, int iy)
{
	t_cpx		z;
	t_cpx		c;

	z = cpx(0., 0.);
	c = cpx(itod(data, ix, 'x') + data->ox, itod(data, iy, 'y') + data->oy);
	return (fast_mandelbrot(z, c, data));
}
