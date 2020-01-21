/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetrell <npetrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:43:44 by npetrell          #+#    #+#             */
/*   Updated: 2020/01/21 18:17:55 by npetrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			put_pxl_to_img(t_fract *data, int x, int y, int color)
{
	if (data->x < SIZE && data->y < SIZE)
	{
		color = mlx_get_color_value(data->mlx_ptr, color);
		ft_memcpy(data->img_ptr + 4 * SIZE * y + x * 4, &color, sizeof(int));
	}
}

static void		mandelbar_put(t_fract *struct_fract)
{
	double		z_re;
	double		z_im;
	double		z_im2;

	struct_fract->c_im = struct_fract->y / struct_fract->zoom +
struct_fract->min_im;
	struct_fract->c_re = struct_fract->x / struct_fract->zoom +
struct_fract->min_re;
	z_re = struct_fract->c_re;
	z_im = struct_fract->c_im;
	struct_fract->iter = 0;
	while (struct_fract->iter < struct_fract->max_iter &&
((pow(z_re, 2) + pow(z_im, 2)) <= 4))
	{
		z_im2 = pow(z_im, 2);
		z_im = 2 * z_re * z_im + struct_fract->c_im;
		z_re = pow(z_re, 2) - z_im2 + struct_fract->c_re;
		struct_fract->iter++;
	}
}

void			*mandelbrot_func(void *data)
{
	t_fract		*struct_fract;

	struct_fract = (t_fract*)data;
	while (struct_fract->y < struct_fract->image_height)
	{
		struct_fract->x = 0;
		while (struct_fract->x < SIZE)
		{
			mandelbar_put(struct_fract);
			(struct_fract->iter == struct_fract->max_iter) ?
put_pxl_to_img(struct_fract, struct_fract->x, struct_fract->y, 0x000000)
			: put_pxl_to_img(struct_fract, struct_fract->x,
struct_fract->y, struct_fract->color * struct_fract->iter);
			struct_fract->x++;
		}
		struct_fract->y++;
	}
	return (NULL);
}

void			mandelbrot_pthread(t_fract *struct_fract)
{
	t_fract		tab[5];
	pthread_t	t[5];
	int			i;

	i = 0;
	while (i < 5)
	{
		ft_memcpy((void*)&tab[i], (void*)struct_fract, sizeof(t_fract));
		tab[i].y = i * 160;
		tab[i].image_height = (i + 1) * 160;
		pthread_create(&t[i], NULL, mandelbrot_func, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(struct_fract->mlx_ptr, struct_fract->win_ptr,
struct_fract->img, 0, 0);
}
