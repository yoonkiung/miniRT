/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:36:28 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/14 15:36:29 by kiyoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	key_hook(int keycode, t_set *set)
{
	if (keycode == 53)
	{
		mlx_destroy_window(set->mlx, set->win);
		exit(1);
	}
	return (0);
}

void	set_keyhook(t_set *set)
{
	mlx_hook(set->win, X_EVENT_DESTROYNOTIFY, 0, &exit_game, set);
	mlx_key_hook(set->win, key_hook, set);
}

void	set_mlx(t_set *set, t_img *img)
{
	set->mlx = mlx_init();
	set->win = mlx_new_window(set->mlx, WIDTH, HEIGHT, "miniRT");
	img->img_ptr = mlx_new_image(set->mlx, WIDTH, HEIGHT);
    img->data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian);
}

void	drawing(t_elements *ele, t_set *set, t_img *img)
{
	int	count_h;
	int	count_w;

	count_h = HEIGHT;
	count_w = WIDTH;
	while (--count_h >= 0)
    {
        count_w = -1;
        while (++count_w < 1600)
				my_mlx_pixel_put(img, count_w, count_h, ele->ray, ele);
    }
    mlx_put_image_to_window(set->mlx, set->win, img->img_ptr, 0, 0);
}