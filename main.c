/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:58:18 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/08 18:43:34 by daechoi          ###   ########.fr       */
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

int hit_sphere(t_sphere sp, t_ray ray)
{
    t_vec3   oc;
    double  a;
    double  b;
    double  c;
    double  discriminant;

    oc = vec3_sub(ray.pos, sp.pos);
    a = vec3_dot(ray.dir, ray.dir);
    b = vec3_dot(oc, ray.dir);
    c = vec3_dot(oc, oc) - ((sp.dia / 2) * (sp.dia / 2));
    discriminant = b * b - a * c;
	//printf("%f\n", discriminant);
    if (discriminant >= 0)
        return (1);
    else
        return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, t_ray *ray, t_sphere sp, t_elements *ele)
{
    int     rgb_color;
    char	*dst;

	(void)ray;
	// int r = 255;
	// int g = 255;
	// int b = 255;

	ele->cam->pos = vec3_set(0, 0, 0);
	double vp_h = 2.0;
	double vp_w = 16.0 / 9.0 * vp_h;
	double focal = 1.0;
	t_vec3 hor = vec3_set(vp_w, 0, 0);
	t_vec3 ver = vec3_set(0, vp_h, 0);
	t_vec3 llc = vec3_sub(vec3_sub(vec3_sub(ele->cam->pos, vec3_dmul(1 / 2, hor)), vec3_dmul(1 / 2, ver)), vec3_set(0, 0, focal));
	double u = (double)x / (double)(1600 - 1);
    double v = (double)y / (double)(900 - 1);
	ray->pos = ele->cam->pos;
	ray->dir = vec3_sub(vec3_add(vec3_add(llc, vec3_dmul(u, hor)), vec3_dmul(v, ver)), ray->pos);
    double t = 0.5 * (vec3_unit(ray->dir).y + 1.0);
    t_vec3 color = vec3_dmul(255.999, vec3_add(vec3_dmul( (1.0 - t), vec3_set(1.0, 1.0, 1.0)), \
                    vec3_dmul(t, vec3_set(0.5, 0.7, 1.0))));
	if (hit_sphere(sp, *ray))
	{
		color.x = 100;
		color.y = 0;
		color.z = 0;
	}
    rgb_color = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
    dst = img->data + (x * (img->bpp / 8)) + ((900 - y - 1) * img->size_l);
	*(unsigned int *)dst = rgb_color;
}

int main(int ac, char **av)
{
	t_elements element;

	if (!init(ac, av, &element))
		ft_exit(1);
	system("leaks miniRT");
	while (1)
	{}
	return (1);
}
