/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:25:45 by kiyoon            #+#    #+#             */
/*   Updated: 2022/12/02 15:25:46 by kiyoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec3	hit_bonus(t_elements *ele, t_hit_record *rec, t_ray *ray)
{
	t_vec3		ret;

	ret = vec3_set(-1, -1, -1);
	hit_sp(ele, rec, ray, &ret);
	hit_pl(ele, rec, ray, &ret);
	hit_cy(ele, rec, ray, &ret);
	hit_co(ele, rec, ray, &ret);
	return (ret);
}

t_vec3	ray_color_bonus(t_elements *ele)
{
	double			t;
	t_hit_record	rec;
	t_vec3			ret;

	rec.tmin = EPSILON;
	rec.tmax = INFINITY;
	ret = hit_bonus(ele, &rec, ele->ray);
	if (ret.x != -1)
		ret = vec3_mul(ret, phong_light(ele, &rec));
	else
	{
		t = 0.5 * (vec3_unit(ele->ray->dir).y + 1.0);
		ret = vec3_dmul(255, vec3_add(vec3_dmul((1.0 - t), vec3_set(1, 1, 1)), \
				vec3_dmul(t, vec3_set(0.5, 0.7, 1.0))));
	}
	return (ret);
}

void	my_mlx_pixel_put_bonus(t_img *img, int x, int y, t_elements *ele)
{
	int		rgb_color;
	char	*dst;
	double	u;
	double	v;
	t_vec3	color;

	u = (double)x / (double)(WIDTH - 1);
	v = (double)y / (double)(HEIGHT - 1);
	fixed_camera(ele->cam, ele->ray);
	ele->ray->dir = vec3_unit(vec3_sub(vec3_add(vec3_add(ele->cam->llc, \
		vec3_dmul(u, ele->cam->hor)), vec3_dmul(v, ele->cam->ver)), \
		ele->ray->pos));
	color = ray_color_bonus(ele);
	rgb_color = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
	dst = img->data + (x * (img->bpp / 8)) + ((HEIGHT - y - 1) * img->size_l);
	*(unsigned int *)dst = rgb_color;
}

int	main(int ac, char **av)
{
	t_elements	ele;
	t_set		set;

	if (!init_bonus(ac, av, &ele))
		ft_exit(1);
	set_mlx(&set, &ele);
	drawing_bonus(&set);
	set_keyhook_bonus(&set);
	print_manual();
	mlx_loop(set.mlx);
	free(set.mlx);
	free_all(&ele, &set);
	return (0);
}
