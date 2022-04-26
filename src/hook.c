/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:59:30 by jalamell          #+#    #+#             */
/*   Updated: 2022/04/21 20:55:48 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_data *data, int x, int y, double mult)
{
	data->ox -= itod(data, x, 'x') * (mult - 1.);
	data->oy -= itod(data, y, 'y') * (mult - 1.);
	data->zoom *= mult;
}

static int	ft_key_hook2(int key, t_data *data)
{
	if (key >= 123 && key <= 126)
	{
		data->ox += data->zoom * data->win_x / 3.
			* (1 - (key - 123) / 2) * (1 - 2 * (key & 1));
		data->oy += data->zoom * data->win_y / 3.
			* ((key - 123) / 2) * (1 - 2 * (key & 1));
	}
	else if (key == 15)
	{
		data->zoom = 2. / data->win_x;
		data->ox = 0.;
		data->oy = 0.;
	}
	else
		return (1);
	return (0);
}

int	ft_key_hook(int key, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (key == 53)
		return (ft_exit(param));
	else if (key >= 18 && key <= 21)
		data->fractal = key - 17;
	else if (key == 49)
		data->mouse_lock = 1 - data->mouse_lock;
	else if (key == 69)
		data->depth *= 2;
	else if (key == 78)
		data->depth = 50;
	else if (key == 67)
		data->color_nb *= 2.;
	else if (key == 75)
		data->color_nb *= .5;
	else if (ft_key_hook2(key, data))
		return (0);
	render(data);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (button == 4)
		zoom(data, x, y, .80);
	else if (button == 5)
		zoom(data, x, y, 1.25);
	else
		return (0);
	render(data);
	return (0);
}

int	ft_move_hook(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (data->mouse_lock)
		return (0);
	data->mouse_x = itod(data, x, 'x') + data->ox;
	data->mouse_y = itod(data, y, 'y') + data->oy;
	if (data->fractal % 2)
		render(data);
	return (0);
}
