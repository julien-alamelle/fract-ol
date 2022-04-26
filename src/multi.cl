double dabs(double f)
{
	if (f < 0.)
		return (-f);
	return (f);
}

int	dtoi(double d)
{
	int	ret;
	int	i;

	d -= (long) d;
	d *= 6.;
	i = (int) d;
	ret = 0xffffff;
	ret -= 0xff << (i / 2 + 2) % 3 * 8;
	ret -= ((int)(dabs(d - 2. * (long)(d * 0.5) - 1.) * 0xff)) << (7 - i) % 3 * 8;
	return (ret);
}

int	len_cmp(double zx, double zy, double lim)
{
	if (zx * zx + zy * zy < lim * lim)
		return (1);
	return (0);
}

void	mult(double *ax, double *ay, double bx, double by)
{
	double	tmpa;
	tmpa = *ax * bx - *ay * by;
	*ay = *ay * bx + *ax * by;
	*ax = tmpa;
}

void	div(double *a, double *b, double c, double d)
{
	double	tmp;
	double	tmpa;
	double	tmpb;

	tmp = 1. / (c * c + d * d);
	tmpa = *a * c + *b * d;
	tmpb = *b * c - *a * d;
	*a = tmpa * tmp;
	*b = tmpb * tmp;
}

int	newton_loop(double zx, double zy, double cx, double cy, int dpt)
{
	int		i;
	double	tmpx;
	double	tmpy;
	double	totx;
	double	toty;

	i = 0;
	while (i++ < dpt)
	{
		totx = zx - cx;
		toty = zy - cy;
		tmpx = zx * zx - zy * zy + 1.;
		tmpy = 2. * zx * zy;
		mult(&totx, &toty, tmpx, tmpy);
		tmpx = 3. * zx * zx - 3. * zy * zy - 2. * zx * cx + 2. * zy * cy + 1.;
		tmpy = 6. * zx * zy - 2. * zy * cx - 2. * zx * cy;
		div(&totx, &toty, tmpx, tmpy);
		zx -= totx;
		zy -= toty;
		if (len_cmp(zx, zy - 1., .000001))
			return (dtoi(0.666666));
		if (len_cmp(zx, zy + 1., .000001))
			return (dtoi(0.333333));
		if (len_cmp(zx - cx, zy - cy, .000001))
			return (dtoi(0.));
	}
	return (0);
}

int	julia_loop(double zx, double zy, double cx, double cy, int dpt, double er, double nbc)
{
	int	i;
	double tmp;

	i = 0;
	while (i++ < dpt && zx * zx + zy * zy < er * er)
	{
		tmp = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = tmp;
	}
	if (zx * zx + zy * zy < er * er)
		return (0);
	return (dtoi((double) i / nbc));
}
__kernel void fractal_calc(__global int *img, int fractal, int wx, int wy, double ox, double oy, double z, double mx, double my, double er, int dpt, double nbc)
{
	int				i;
	int				j;
	unsigned int	color;
	double			r;
	double			g;
	double			b;

	i = get_global_id(0);
	r = 0.;
	g = 0.;
	b = 0.;
	ox += ((double)(2 * (i % wx) - wx)) * z;
	oy -= ((double)(2 * i / wx - wy)) * z;
	j = 4;
	z *= .25;
	while (j--)
	{
		if (fractal == 1)
			color = julia_loop(ox + (double)(j / 2 * 2 - 1) * z, oy + (double)(j % 2 * 2 - 1) * z, mx, my, dpt, er, nbc);
		if (fractal == 2)
			color = julia_loop(0., 0., ox + (double)(j / 2 * 2 - 1) * z, oy + (double)(j % 2 * 2 - 1) * z, dpt, er, nbc);
		if (fractal == 3)
			color = newton_loop(ox + (double)(j / 2 * 2 - 1) * z, oy + (double)(j % 2 * 2 - 1) * z, mx, my, dpt);
		if (fractal == 4)
			color = newton_loop(ox / 3., oy / 3., ox + (double)(j / 2 * 2 - 1) * z, oy + (double)(j % 2 * 2 - 1) * z, dpt);
		r += (double)(color >> 16) / 4.;
		g += (double)(color >> 8 & 0xff) / 4.;
		b += (double)(color & 0xff) / 4.;
	}
	color = (((int) r) << 16) + (((int) g) << 8) + ((int) b);
	img[i] = color;
}
