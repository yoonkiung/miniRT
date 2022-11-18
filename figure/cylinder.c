/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:31:49 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/17 19:31:50 by kiyoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

bool	hit_circle(t_cylinder *cy, t_ray *ray, t_hit_record *rec, int position)
{
	double	denominator;
	double	numerator;
	double	root;
	t_vec3	normal;
	t_vec3	center;

	normal = vec3_dmul((double)position, cy->norm);
	center = vec3_add(cy->pos, vec3_dmul(cy->height / 2, normal));
	denominator = vec3_dot(normal, ray->dir);
	if (fabs(denominator) < EPSILON)
		return (false);
	numerator = vec3_dot(vec3_sub(center, ray->pos), normal);
	root = numerator / denominator;
	if (root < rec->tmin || rec->tmax < root)
		return (false);
	rec->t = root;
	rec->pos = ray_at(ray, root);
	rec->norm = normal;
	if (vec3_length(vec3_sub(rec->pos, center)) - (cy->dia / 2) > EPSILON)
		return (false);
	set_isfront(ray, rec);
	return (true);
}

bool hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	double	a;
	double	half_b;
	double	c;
	double	det;
	double	sqrtd;
	double	root;
	t_vec3	cp;

	a = vec3_length(vec3_cross(ray->dir, cy->norm)) * vec3_length(vec3_cross(ray->dir, cy->norm));
	half_b = vec3_dot(vec3_cross(ray->dir, cy->norm), vec3_cross(vec3_sub(ray->pos, cy->pos), cy->norm));
	c = vec3_length(vec3_cross(vec3_sub(ray->pos, cy->pos), cy->norm)) * vec3_length(vec3_cross(vec3_sub(ray->pos, cy->pos), cy->norm)) - (cy->dia / 2) * (cy->dia / 2);
	det = (half_b * half_b) - a * c;
	if (det <= 0)
		return (false);
	sqrtd = sqrt(det);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (false);
	}
	rec->pos = ray_at(ray, rec->t);
	cp = vec3_sub(rec->pos, cy->pos);
	if (fabs(vec3_dot(cp, cy->norm)) > cy->height / 2)
		return (hit_circle(cy, ray, rec, 1)
				|| hit_circle(cy, ray, rec, -1));
	rec->norm = vec3_unit(vec3_sub(cp, vec3_dmul(vec3_dot(cp, cy->norm), cy->norm)));
	set_isfront(ray, rec);
	return (true);
}

void	hit_cy(t_elements *ele, t_hit_record *rec, t_ray *ray, t_vec3 *ret)
{
	t_cylinder	*cur;

	cur = ele->cylinder;
	while (cur)
	{
		if (hit_cylinder(cur, ray, rec))
		{
			*ret = vec3_set(cur->red, cur->green, cur->blue);
			rec->tmax = rec->t;
		}
		cur = cur->next;
	}
}