/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:34:57 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/21 16:07:04 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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

bool	hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
    t_vec3  oc;
    double  a;
    double  half_b;
    double  c;
    double  discriminant;
	double	sqrtd;
	double	root;
	printf("------------------------\n");
	printf("ray->pos : %lf %lf %lf\n", ray->pos.x, ray->pos.y, ray->pos.z);
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
		return (false);
	rec->t = root;
	rec->pos = ray_at(ray, root);
	rec->norm = vec3_dmul(1 / (sp->dia / 2), vec3_sub(rec->pos, sp->pos));
	set_isfront(ray, rec);
	printf("ray->pos : %lf %lf %lf\n", ray->pos.x, ray->pos.y, ray->pos.z);
	return (true);
}

void	hit_sp(t_elements *ele, t_hit_record *rec, t_ray *ray, t_vec3 *ret)
{
	t_sphere	*cur;

	cur = ele->sphere;
	while (cur)
	{
		if (hit_sphere(cur, ray, rec))
		{
			*ret = vec3_set(cur->red, cur->green, cur->blue);
			rec->tmax = rec->t;
		}
		cur = cur->next;
	}
}
