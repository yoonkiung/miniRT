/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:58:18 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/17 16:52:59 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_isfront(t_ray *ray, t_hit_record *rec)
{
	if (vec3_dot(ray->dir, rec->norm) < 0)
		rec->isfront = true;
	else
	{
		rec->isfront = false;
		rec->norm = vec3_dmul(-1.0, rec->norm);
	}
}

t_vec3 hit(t_elements *ele, t_hit_record *rec, t_ray *ray)
{
	t_vec3		ret;

	ret = vec3_set(-1, -1, -1);
	hit_sp(ele, rec, ray, &ret);
	hit_pl(ele, rec, ray, &ret);
	hit_cy(ele, rec, ray, &ret);
	return (ret);
}

t_vec3	ray_color(t_elements *ele)
{
	double 			t;
	t_hit_record	rec;
	t_vec3 			ret;

	rec.tmin = 1e-6;
	rec.tmax = INFINITY;
	ret = hit(ele, &rec, ele->ray);
	if (ret.x != -1)
		ret = vec3_mul(ret, phong_light(ele, &rec));
	else
	{
		t = 0.5 * (vec3_unit(ele->ray->dir).y + 1.0);
		ret = vec3_dmul(255, vec3_add(vec3_dmul( (1.0 - t), vec3_set(1, 1, 1)), \
                    vec3_dmul(t, vec3_set(0.5, 0.7, 1.0))));
	}
	return (ret);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, t_ray *ray, t_elements *ele)
{
    int		rgb_color;
    char	*dst;
	double	vp_h = 2.0;
	double	vp_w = ((double)WIDTH / (double)HEIGHT) * vp_h;
	double	focal = 2.0;
	t_vec3 hor = vec3_set(vp_w, 0, 0);
	t_vec3 ver = vec3_set(0, vp_h, 0);
	t_vec3 llc = vec3_set((0 - vp_w / 2) + ele->cam->norm.x, (0 - vp_h / 2) + ele->cam->norm.y, -focal + ele->cam->norm.z);
	double u = (double)x / (double)(WIDTH - 1);
    double v = (double)y / (double)(HEIGHT - 1);
	ray->pos = ele->cam->pos;
    ray->dir = vec3_unit(vec3_sub(vec3_add(vec3_add(llc, vec3_dmul(u, hor)), vec3_dmul(v, ver)), ray->pos));
	t_vec3 color = ray_color(ele);
    rgb_color = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
    dst = img->data + (x * (img->bpp / 8)) + ((HEIGHT - y - 1) * img->size_l);
	*(unsigned int *)dst = rgb_color;
}

int main(int ac, char **av)
{
	t_elements	ele;
	t_set 		set;

	if (!init(ac, av, &ele))
		ft_exit(1);
	set_mlx(&set, &ele);
    drawing(&set);
	set_keyhook(&set);
	mlx_loop(set.mlx);
	free(set.mlx);
	return (0);
}
