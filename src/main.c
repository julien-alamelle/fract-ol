/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:18:30 by jalamell          #+#    #+#             */
/*   Updated: 2021/12/27 16:10:28 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "stdio.h"
#include "stdlib.h"

int	keykw(int key, void *param)
{
	(void) param;
	if (key == 53)
		exit(0);
	printf("%d\n", key);
	return (0);
}

int	main(int ac, char **av)
{
	void	*mlx_ptr;
	void	*win_ptr;

	(void) ac;
	(void) av;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "test");
	mlx_key_hook(win_ptr, keykw, 0);
	mlx_loop(mlx_ptr);
}
