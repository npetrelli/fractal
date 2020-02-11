/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse_press.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:40:55 by npetrell          #+#    #+#             */
/*   Updated: 2020/02/09 22:01:47 by npetrell         ###   ########.fr       */
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
	0, 10, 0x3a8888, "iteration: ");
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	107, 10, 0xC5329F, nb);
	free(nb);
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 30, 0x3a8888, "colors change key: 1");
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 50, 0x3a8888, "zoom up/down: mouse's scroll wheel");
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 70, 0x3a8888, "iteration up/down key: +, -");
	mlx_string_put(struct_fract->params.mlx_ptr, struct_fract->params.win_ptr,
	0, 90, 0x3a8888, "move fractal keys: UP, DOWN, LEFT, RIGHT");
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
		struct_fract->min_re += 0.1;
	if (key == 124 || key == 2)
		struct_fract->min_re -= 0.1;
	if (key == 125 || key == 1)
		struct_fract->min_im -= 0.1;
	if (key == 126 || key == 13)
		struct_fract->min_im += 0.1;
	if (key == 18 || key == 83)
		struct_fract->clr.step++;
	mlx_clear_window(struct_fract->params.mlx_ptr,
	struct_fract->params.win_ptr);
	ft_bzero(struct_fract->params.img_ptr, 0);
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
	if (x >= 0 && y >= 0 && x <= 50 && y <= 50)
	{
		struct_fract->params.mlx = mlx_init();
		struct_fract->params.win = mlx_new_window(struct_fract->params.mlx,
801, 401, "main");
		draw_menu(struct_fract);
		mlx_hook(struct_fract->params.win, 17, 1 << 0,
		ft_close, struct_fract);
		mlx_mouse_hook(struct_fract->params.win, mouse_press1, struct_fract);
		mlx_loop(struct_fract->params.mlx);
	}
	draw(struct_fract);
	return (0);
}

int			julia_motion(int x, int y, t_fract *fractol)
{
	if (x >= 0 && x <= SIZE && y >= 0 && y <= SIZE)
	{
		fractol->k_re = 4 * ((double)x / SIZE - 0.5);
		fractol->k_im = 4 * ((double)(SIZE - y) / SIZE - 0.5);
		fract_pthread_create(fractol);
	}
	return (0);
}
