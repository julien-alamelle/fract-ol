/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl_to_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:47:04 by jalamell          #+#    #+#             */
/*   Updated: 2022/05/31 15:46:33 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

int	simple_hsl_to_rgb(double hue)
{
	int		ret;
	int		i;

	hue -= (long) hue;
	hue *= 6.;
	i = (int) hue;
	ret = 0xffffff;
	ret -= 0xff << (i / 2 + 2) % 3 * 8;
	ret -= ((int)(fabs(fmod(hue, 2.) - 1.) * 0xff)) << (7 - i) % 3 * 8;
	return (ret);
}
