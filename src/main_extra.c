/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:43:58 by jalamell          #+#    #+#             */
/*   Updated: 2022/05/27 15:54:50 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include "fractol_extra.h"
#include <math.h>

int	ft_exit(void *param)
{
	t_data	*data;

	data = param;
	if (data)
		data_del(data);
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	data_init(&data);
	if (data_add_input(&data, ac - 1, av + 1))
		exit(0);
	render(&data);
	mlx_hook(data.win_ptr, 17, 0, ft_exit, &data);
	mlx_hook(data.win_ptr, 2, 0, ft_key_hook, &data);
	mlx_hook(data.win_ptr, 4, 0, ft_mouse_hook, &data);
	mlx_hook(data.win_ptr, 6, 0, ft_move_hook, &data);
	mlx_loop(data.mlx_ptr);
}
