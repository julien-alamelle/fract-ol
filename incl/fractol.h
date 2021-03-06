/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:01:10 by jalamell          #+#    #+#             */
/*   Updated: 2022/05/31 15:53:04 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

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
}	t_data;

void	data_init(t_data *data);
void	data_del(t_data *data);
//int		mandelbrot(t_data *data, int ix, int iy);
int		simple_hsl_to_rgb(double hue);
double	itod(t_data *data, int coord, char axis);
t_cpx	atoz(char *s);
int		data_add_input(t_data *data, int ac, char **av);
int		ft_key_hook(int key, void *param);
int		ft_mouse_hook(int button, int x, int y, void *param);
int		ft_move_hook(int x, int y, void *param);
int		ft_exit(void *param);
void	render(t_data *data);

t_cpx	cpx(double r, double i);
t_cpx	cpx_add(t_cpx cpx1, t_cpx cpx2);
t_cpx	cpx_mlt(t_cpx cpx1, t_cpx cpx2);
t_cpx	cpx_neg(t_cpx cpx);
t_cpx	cpx_inv(t_cpx cpx);

#endif
