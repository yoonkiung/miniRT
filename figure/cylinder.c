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

int	cy_boundary(t_cylinder *cy, t_vec3 at_point)
{
	double	hit_height;
	double	max_height;

	hit_height = vec3_dot(vec3_sub(at_point, cy->pos), vec3_unit(cy->norm));
	max_height = cy->height / 2;
	if (fabs(hit_height) > max_height)
		return (0);
	return (1);
}

t_vec3      get_cylinder_normal(t_cylinder *cy, t_vec3 at_point, double hit_height)
{
    t_vec3 hit_center;
    t_vec3 normal;

    hit_center = vec3_add(cy->pos, vec3_dmul(hit_height, vec3_unit(cy->norm)));
    normal = vec3_sub(at_point, hit_center);

    return (vec3_unit(normal));
}

int      hit_cylinder_cap(t_cylinder *cy, t_ray *ray, t_hit_record *rec, double height)
{
    const double r = cy->dia / 2;
    const t_vec3    circle_center = vec3_add(cy->pos, vec3_dmul(height, vec3_unit(cy->norm)));
    const double root = vec3_dot(vec3_sub(circle_center, ray->pos), vec3_unit(cy->norm)) / vec3_dot(ray->dir, vec3_unit(cy->norm));
    // printf("ray->pos : %lf %lf %lf\n", ray->pos.x, ray->pos.y, ray->pos.z);
	const double diameter = vec3_length(vec3_sub(circle_center, ray_at(ray, root)));
    // printf("---------------\n");
	// printf("1\n");
    // printf("%lf %lf\n", r, diameter);
	if (fabs(r) < fabs(diameter))
		return (0);
    // printf("2\n");
    if (root < rec->tmin || rec->tmax < root)
       return (0);
    // printf("3\n");
    rec->t = root; 
    rec->pos = ray_at(ray, root);
    rec->tmax = rec->t;
    if (0 < height)
        rec->norm = cy->norm;
    else
        rec->norm = vec3_dmul(-1, cy->norm);
    set_isfront(ray, rec);
    return (1);
}

int      hit_cylinder_side(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
    double  a;
	double  half_b;
    double  c;
    t_vec3  u;
    t_vec3  o;
    t_vec3  delta_P;
    double r;

    double discriminant;
    double sqrtd;
    double root;
    double hit_height;
    
    u = ray->dir;
    o = vec3_unit(cy->norm);
    r = cy->dia / 2;
    delta_P = vec3_sub(ray->pos, cy->pos);
    a = vec3_length(vec3_cross(u, o)) * vec3_length(vec3_cross(u, o));
    half_b = vec3_dot(vec3_cross(u, o), vec3_cross(delta_P, o));
    c = vec3_length(vec3_cross(delta_P, o)) * vec3_length(vec3_cross(delta_P, o)) - pow(r, 2);
    discriminant = half_b * half_b - a * c;
    if (discriminant < 0) 
        return (0);
    sqrtd = sqrt(discriminant); 
    root = (-half_b - sqrtd) / a;
    if (root < rec->tmin || rec->tmax < root)
    {
    root = (-half_b + sqrtd) / a; 
        if (root < rec->tmin || rec->tmax < root)
        return (0);
    }
    if (!(hit_height = cy_boundary(cy, ray_at(ray, root))))
        return (0);

    rec->t = root;
    rec->pos = ray_at(ray, root);
    rec->norm = get_cylinder_normal(cy, rec->pos, hit_height);
	set_isfront(ray, rec); 
    return (1);
}

int hit_cylinder(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
    int result;

    result = 0;
    result += hit_cylinder_cap(cy, ray, rec, cy->height / 2);
    result += hit_cylinder_cap(cy, ray, rec, (-cy->height) / 2);
    result += hit_cylinder_side(cy, ray, rec);
    return (result);
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