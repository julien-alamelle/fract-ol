/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:25:27 by jalamell          #+#    #+#             */
/*   Updated: 2022/04/21 15:30:56 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_struct.h"

static double	atod(char **s)
{
	double	ret;
	double	exp;

	ret = 0;
	exp = 1;
	while (**s <= '9' && **s >= '0')
		ret = 10 * ret + (*((*s)++) - '0');
	if (**s == '.')
		++(*s);
	while (**s <= '9' && **s >= '0')
	{
		exp *= .1;
		ret += exp * (*((*s)++) - '0');
	}
	return (ret);
}

t_cpx	atoz(char *s)
{
	t_cpx	ret;
	double	d;
	int		sign;
	int		loop;

	loop = 2;
	ret.r = 0;
	ret.i = 0;
	while (loop--)
	{
		sign = 1;
		d = 1.;
		if (*s == '-' || *s == '+')
			if (*(s++) == '-')
				sign = -1;
		if (*s != 'i')
			d = atod(&s);
		if (*s == 'i')
		{
			ret.i = d * sign;
			return (ret);
		}
		ret.r = d * sign;
	}
	return (ret);
}

static int	arg_check(int ac, char **av)
{
	int			i;
	int			state;
	const int	fsm[4][12] = {{1, -1, -1, -1, -1, -1, -1, -1, 3, 3, 3, -1},
	{8, 8, 10, 4, 4, 7, 7, 7, 8, 10, 10, -1},
	{2, 2, -1, 5, 6, -1, -1, -1, 9, -1, -1, -1},
	{11, 11, -1, 11, 11, -1, 11, 11, 11, 11, 11, -1}};

	if (!ac)
		return (0);
	i = -1;
	state = 0;
	while (av[0][++i])
	{
		if ((av[0][i] == '+' || av[0][i] == '-') && state >= 0)
			state = fsm[0][state];
		else if (av[0][i] >= '0' && av[0][i] <= '9' && state >= 0)
			state = fsm[1][state];
		else if (av[0][i] == '.' && state >= 0)
			state = fsm[2][state];
		else if (av[0][i] == 'i' && state >= 0)
			state = fsm[3][state];
		else
			return (1);
	}
	return ((state < 8) || arg_check(ac - 1, av + 1));
}

int	data_add_input(t_data *data, int ac, char **av)
{
	t_cpx	var;

	if (ac <= 0 || (**av != 'j' && **av != 'm' && **av != 'n' && **av != 'f')
		|| (*av)[1])
		return (write(0, "at least 1 arg in j m n f\n", 26));
	if (arg_check(ac - 1, av + 1))
		return (write(0, "other argument must be complex : -.203+.695i\n", 45));
	if (**av == 'j')
		data->fractal = 1;
	if (**av == 'm')
		data->fractal = 2;
	if (**av == 'n')
		data->fractal = 3;
	if (**av == 'f')
		data->fractal = 4;
	if (data->fractal == 1 && ac++ > 1)
	{
		var = atoz((av++)[1]);
		data->mouse_lock = 1;
		data->mouse_x = var.r;
		data->mouse_y = var.i;
	}
	return (0);
}
