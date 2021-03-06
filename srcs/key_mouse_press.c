/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_press.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:40:55 by npetrell          #+#    #+#             */
/*   Updated: 2020/02/12 19:35:19 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			ft_close(void)
{
	exit(1);
	return (0);
}

void		draw(t_fract *struct_fract)
{
	char	*nb;

	fract_pthread_create(struct_fract);
	nb = ft_itoa(struct_fract->max_iter);
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 20, 0x3a8888, "choose other fractals: ");
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 40, 0xC71585, "click here");
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 60, 0x3a8888, "iteration: ");
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	107, 60, 0xC5329F, nb);
	free(nb);
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 80, 0x3a8888, "colors change key: 1");
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 100, 0x3a8888, "zoom up/down: mouse's scroll wheel");
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 120, 0x3a8888, "iteration up/down key: +, -");
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 140, 0x3a8888, "move fractal keys: UP, DOWN, LEFT, RIGHT");
	if (struct_fract->fractol == 2)
		mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.\
	win_ptr, 0, 160, 0xC71585, "click left mouse, if you wanna start moving");
}

int			key_press(int key, t_fract *struct_fract)
{
	if (key == 53)
		exit(0);
	if (key == 27 || key == 78)
	{
		struct_fract->max_iter--;
		if (struct_fract->max_iter < 0)
			struct_fract->max_iter = 0;
	}
	if (key == 24 || key == 69)
		struct_fract->max_iter++;
	if (key == 123 || key == 0)
		struct_fract->min_re += 0.05;
	if (key == 124 || key == 2)
		struct_fract->min_re -= 0.05;
	if (key == 125 || key == 1)
		struct_fract->min_im -= 0.05;
	if (key == 126 || key == 13)
		struct_fract->min_im += 0.05;
	if (key == 18 || key == 83)
		struct_fract->clr.step++;
	draw(struct_fract);
	return (0);
}

int			mouse_press(int mouse, int x, int y, t_fract *struct_fract)
{
	if (mouse == 4)
	{
		struct_fract->min_re = (x / struct_fract->zoom +
struct_fract->min_re) - (x / (struct_fract->zoom * 1.2));
		struct_fract->min_im = (y / struct_fract->zoom +
struct_fract->min_im) - (y / (struct_fract->zoom * 1.2));
		struct_fract->zoom *= 1.2;
	}
	if (mouse == 5)
	{
		struct_fract->min_re = (x / struct_fract->zoom +
struct_fract->min_re) - (x / (struct_fract->zoom / 1.2));
		struct_fract->min_im = (y / struct_fract->zoom +
struct_fract->min_im) - (y / (struct_fract->zoom / 1.2));
		struct_fract->zoom /= 1.2;
	}
	if (mouse == 1)
		struct_fract->params.pressed = 1;
	if (mouse == 2)
		struct_fract->params.pressed = 0;
	if (x >= 0 && y >= 0 && x <= 60 && y <= 60)
		init_main(struct_fract);
	draw(struct_fract);
	return (0);
}

int			julia_motion(int x, int y, t_fract *fractol)
{
	if (fractol->params.pressed == 1)
	{
		fractol->k_re = 4 * ((double)x / SIZE - 0.5);
		fractol->k_im = 4 * ((double)(SIZE - y) / SIZE - 0.5);
		fract_pthread_create(fractol);
		mlx_string_put(fractol->params.mlx_ptr, fractol->params.win_ptr,
	0, 10, 0xC71585, "click right mouse, if you wanna stop moving");
	}
	return (0);
}
