/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:58:18 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/21 16:45:34 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	hit(t_elements *ele, t_hit_record *rec, t_ray *ray)
{
	t_vec3		ret;

	ret = vec3_set(-1, -1, -1);
	hit_sp(ele, rec, ray, &ret);
	hit_pl(ele, rec, ray, &ret);
	return (ret);
}

t_vec3	ray_color(t_elements *ele)
{
	t_hit_record	rec;
	t_vec3			ret;

	rec.tmin = 1e-6;
	rec.tmax = INFINITY;
	ret = hit(ele, &rec, ele->ray);
	if (ret.x != -1)
		ret = vec3_mul(ret, phong_light(ele, &rec));
	else
		ret = vec3_set(255, 255, 255);
	return (ret);
}

void	init_camera(t_camera *cam)
{
	double	vp_h;
	double	vp_w;
	double	focal;

	vp_h = 2.0;
	vp_w = ((double)WIDTH / (double)HEIGHT) * vp_h;
	focal = (vp_w / 2.0 * 90) / cam->fov;
	cam->hor = vec3_set(cam->pos.x + vp_w, cam->pos.y, cam->pos.z);
	cam->ver = vec3_set(cam->pos.x, cam->pos.y + vp_h, cam->pos.z);
	cam->llc = vec3_set((cam->pos.x - vp_w / 2) \
		+ cam->norm.x, (cam->pos.y - vp_h / 2) + cam->norm.y, -focal + cam->norm.z);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, t_elements *ele)
{
	int		rgb_color;
	char	*dst;
	double	u;
	double	v;
	t_vec3	color;

	u = (double)x / (double)(WIDTH - 1);
	v = (double)y / (double)(HEIGHT - 1);
	init_camera(ele->cam);
	ele->ray->pos = ele->cam->pos;
	ele->ray->dir = vec3_unit(vec3_sub(vec3_add(vec3_add(ele->cam->llc, \
		vec3_dmul(u, ele->cam->hor)), vec3_dmul(v, ele->cam->ver)), \
		ele->ray->pos));
	color = ray_color(ele);
	rgb_color = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
	dst = img->data + (x * (img->bpp / 8)) + ((HEIGHT - y - 1) * img->size_l);
	*(unsigned int *)dst = rgb_color;
}

int	main(int ac, char **av)
{
	t_elements	ele;
	t_set		set;

	if (!init(ac, av, &ele))
		ft_exit(1);
	set_mlx(&set, &ele);
	drawing(&set);
	set_keyhook(&set);
	mlx_loop(set.mlx);
	free(set.mlx);
	return (0);
}
