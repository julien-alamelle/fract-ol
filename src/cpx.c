/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:57:48 by jalamell          #+#    #+#             */
/*   Updated: 2021/12/30 17:07:11 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_struct.h"
#include <math.h>

t_cpx	cpx(double r, double i)
{
	t_cpx	ret;

	ret.r = r;
	ret.i = i;
	return (ret);
}

t_cpx	cpx_add(t_cpx cpx1, t_cpx cpx2)
{
	t_cpx	ret;

	ret.r = cpx1.r + cpx2.r;
	ret.i = cpx1.i + cpx2.i;
	return (ret);
}

t_cpx	cpx_mlt(t_cpx cpx1, t_cpx cpx2)
{
	t_cpx	ret;

	ret.r = cpx1.r * cpx2.r - cpx1.i * cpx2.i;
	ret.i = cpx1.r * cpx2.i + cpx1.i * cpx2.r;
	return (ret);
}

t_cpx	cpx_neg(t_cpx cpx)
{
	t_cpx	ret;

	ret.r = -cpx.r;
	ret.i = -cpx.i;
	return (ret);
}

t_cpx	cpx_inv(t_cpx cpx)
{
	t_cpx			ret;
	const double	length = hypot(cpx.r, cpx.i);

	ret.r = cpx.r / length;
	ret.i = -cpx.i / length;
	return (ret);
}
