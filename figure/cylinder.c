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

t_vec3      get_cylinder_normal(t_cylinder *cy, t_vec3 at_point, double hit_height)
{
    t_vec3	hit_center;
    t_vec3	normal;

    hit_center = vec3_add(cy->pos, vec3_dmul(hit_height, cy->norm));
    normal = vec3_sub(at_point, hit_center);
    return (vec3_unit(normal));
}

bool hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	double	a;
	double	half_b;
	double	c;
	double	det;
	double	sqrtd;
	double	root;

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
	rec->t = root;
	rec->pos = ray_at(ray, root);
	// rec->norm = get_cylinder_normal(cy, rec->pos, 0);
	rec->norm = cy->norm;
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