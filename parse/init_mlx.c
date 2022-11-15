/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:36:28 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/15 20:35:46 by daechoi          ###   ########.fr       */
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
	else if (keycode == 12)
		move_x(set->select, INCREASE);
	else if (keycode == 0)
		move_x(set->select, DECREASE);
	else if (keycode == 13)
		move_y(set->select, INCREASE);
	else if (keycode == 1)
		move_y(set->select, DECREASE);
	else if (keycode == 14)
		move_z(set->select, INCREASE);
	else if (keycode == 2)
		move_z(set->select, DECREASE);
	else if (keycode == 15)
		rotate_x(set->select, INCREASE);
	else if (keycode == 3)
		rotate_x(set->select, DECREASE);
	// else if (keycode == 17)
	// else if (keycode == 5)
	// else if (keycode == 16)
	// else if (keycode == 4)
	drawing(set);
	return (0);
}

void	set_keyhook(t_set *set)
{
	mlx_hook(set->win, X_EVENT_DESTROYNOTIFY, 0, &exit_game, set);
	mlx_key_hook(set->win, key_hook, set);
}

void	set_mlx(t_set *set, t_elements *ele)
{
	set->ele = ele;
	set->mlx = mlx_init();
	set->win = mlx_new_window(set->mlx, WIDTH, HEIGHT, "miniRT");
	set->select = init_select(set->ele->cam);
	set->img = ft_malloc(sizeof(t_img));
	set->img->img_ptr = mlx_new_image(set->mlx, WIDTH, HEIGHT);
    set->img->data = mlx_get_data_addr(set->img->img_ptr, &set->img->bpp, &set->img->size_l, &set->img->endian);
}

void	drawing(t_set *set)
{
	int	count_h;
	int	count_w;

	count_h = HEIGHT;
	count_w = WIDTH;
	while (--count_h >= 0)
    {
        count_w = -1;
        while (++count_w < 1600)
				my_mlx_pixel_put(set->img, count_w, count_h, set->ele->ray, set->ele);
    }
    mlx_put_image_to_window(set->mlx, set->win, set->img->img_ptr, 0, 0);
}