/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:58:18 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/11 17:40:21 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

typedef struct  s_img
{
    void    *img_ptr;
    char    *data;
    int     size_l;
    int     bpp;
    int     endian;
}   t_img;

int	exit_game(t_set *set)
{
	mlx_destroy_window(set->mlx, set->win);
	exit(0);
}

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

bool hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
    t_vec3  oc;
    double  a;
    double  half_b;
    double  c;
    double  discriminant;
	double	sqrtd;
	double	root;

    oc = vec3_sub(ray->pos, sp->pos);
    a = vec3_dot(ray->dir, ray->dir);
    half_b = vec3_dot(oc, ray->dir);
    c = vec3_dot(oc, oc) - ((sp->dia / 2) * (sp->dia / 2));
    discriminant = half_b * half_b - a * c;
	if (discriminant <= 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (false);
	}
	rec->t = root;
	rec->pos = ray_at(ray, root);
	rec->norm = vec3_dmul(1 / (sp->dia / 2), vec3_sub(rec->pos, sp->pos));
	set_isfront(ray, rec);
	return (true);
}

bool hit(t_elements *ele, t_hit_record *rec, t_ray *ray)
{
	//t_hitten_object	hobj;
	bool		ishit;
	t_sphere	*cur;

	ishit = false;
	cur = ele->sphere;
	while (cur)
	{
		if (hit_sphere(cur, ray, rec))
		{
			ishit = true;
			rec->tmax = rec->t;
		}
		cur = cur->next;
	}
	return (ishit);
}

t_vec3	ray_color(t_elements *ele)
{
	double 			t;
	t_hit_record	rec;
	t_vec3 			ret;
	bool 			temp;

	rec.tmin = 1e-6;
	rec.tmax = INFINITY;
	temp = hit(ele, &rec, ele->ray);
	if (temp)
	{
		// ret = vec3_dmul(255, vec3_dmul(0.5, vec3_add(rec.norm, vec3_set(1, 1, 1))));
		ret = vec3_set(190,100,0);
		ret = vec3_mul(ret, phong_light(ele, &rec));
	}
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
    int     rgb_color;
    char	*dst;

	ele->cam->pos = vec3_set(0, 0, 0);
	double vp_h = 2.0;
	double vp_w = (1600.0 / 900.0) * vp_h;
	double focal = 2.0;
	t_vec3 hor = vec3_set(vp_w, 0, 0);
	t_vec3 ver = vec3_set(0, vp_h, 0);
	// t_vec3 llc = vec3_sub(vec3_sub(vec3_set(ele->cam->pos.x - 1/2 * vp_h, ele->cam->pos.y - 1/2 * vp_h, ele->cam->pos.z - 1/2 * vp_h)), vec3_dmul(1/2)), vec3_set(0, 0, focal));
	t_vec3 llc = vec3_set(0 - vp_w / 2, 0 - vp_h / 2, -focal);
	double u = (double)x / (double)(1600 - 1);
    double v = (double)y / (double)(900 - 1);
	ray->pos = ele->cam->pos;
    ray->dir = vec3_unit(vec3_sub(vec3_add(vec3_add(llc, vec3_dmul(u, hor)), vec3_dmul(v, ver)), ray->pos));
	t_vec3 color = ray_color(ele);
    rgb_color = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
    dst = img->data + (x * (img->bpp / 8)) + ((900 - y - 1) * img->size_l);
	*(unsigned int *)dst = rgb_color;
}

int main(int ac, char **av)
{
	t_elements	*ele;
	t_img 		img;
	t_set 		set;

	// if (!init(ac, av, &ele))
	// 	ft_exit(1);
	(void)ac;
	(void)av;
    int count_h = 900;
	int count_w;
	set.mlx = mlx_init();
	set.win = mlx_new_window(set.mlx, 1600, 900, "miniRT");
	img.img_ptr = mlx_new_image(set.mlx, 1600, 900);
    img.data = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	ele = malloc(sizeof(t_elements));
	ele->sphere = malloc(sizeof(t_sphere));
	ele->sphere->next = malloc(sizeof(t_sphere));
	ele->sphere->next->next = NULL;
	ele->cam = malloc(sizeof(t_camera));
	ele->ray = malloc(sizeof(t_ray));
	ele->sphere->pos = vec3_set(-3, 0, -5);
	ele->sphere->dia = 2.0;
	ele->sphere->next->pos = vec3_set(0,0,-5);
	ele->sphere->next->dia = 2.0;
	ele->sphere->next->next = malloc(sizeof(t_sphere));
	ele->sphere->next->next->pos = vec3_set(0, -106, -10);
	ele->sphere->next->next->dia = 200;
	ele->sphere->next->next->next = NULL;
	ele->sphere->next->next->next = malloc(sizeof(t_sphere));
	ele->sphere->next->next->next->pos = vec3_set(3, 0, -5);
	ele->sphere->next->next->next->dia = 2.0;
	ele->sphere->next->next->next->next = NULL;
	ele->amb = malloc(sizeof(t_ambient));
	ele->amb->red = 1;
	ele->amb->green = 1;
	ele->amb->blue = 1;
	ele->amb->ratio = 0.1;
	ele->light = malloc(sizeof(t_light));
	ele->light->pos = vec3_set(0, 10, 0);
	ele->light->ratio = 0.5;
    while (--count_h >= 0)
    {
        count_w = -1;
        while (++count_w < 1600)
				my_mlx_pixel_put(&img, count_w, count_h, ele->ray, ele);
    }
    mlx_put_image_to_window(set.mlx, set.win, img.img_ptr, 0, 0);
	//mlx_hook(set.win, X_EVENT_KEYPRESS, 0, &exit_game, &set);
	mlx_hook(set.win, X_EVENT_DESTROYNOTIFY, 0, &exit_game, &set);
	mlx_loop(set.mlx);
	free(set.mlx);
	return (0);
}
