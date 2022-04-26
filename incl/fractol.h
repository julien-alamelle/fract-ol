/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:11:08 by jalamell          #+#    #+#             */
/*   Updated: 2022/04/26 14:56:42 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "fractol_struct.h"

int		mandelbrot(t_data *data, int ix, int iy);
int		simple_hsl_to_rgb(double hue);
double	itod(t_data *data, int coord, char axis);
t_cpx	atoz(char *s);
int		data_add_input(t_data *data, int ac, char **av);
int		ft_key_hook(int key, void *param);
int		ft_mouse_hook(int button, int x, int y, void *param);
int		ft_move_hook(int x, int y, void *param);
int		ft_exit(void *param);
void	render(t_data *data);

#endif
