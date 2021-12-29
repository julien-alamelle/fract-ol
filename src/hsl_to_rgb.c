/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl_to_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:47:04 by jalamell          #+#    #+#             */
/*   Updated: 2021/12/27 17:22:42 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

int	simple_hst_to_rgb(double hue)
{
	int		ret;
	int		ih;

	hue = fmod(hue, 2. * M_PI) / (M_PI / 3.);
	ih = (int) hue;
	ret = 0xffffff;
	ret -= 0xff << (ih / 2 + 2) % 3 * 2;
	ret -= ((int) fabs(fmod(hue, 2.) - 1.)) << (7 - ih) % 3 * 2;
	return (ret);
}
