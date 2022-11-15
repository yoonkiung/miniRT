/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:10:03 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/15 16:51:37 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
    return (vec3_sub(v, vec3_dmul(vec3_dot(v, n) * 2, n)));
}

bool	in_shadow(t_elements *ele, t_ray *light_ray)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = INFINITY;
	if (hit(ele, &rec, light_ray))
		return (true);
	return (false);
}

t_vec3	point_light(t_elements *ele, t_hit_record *rec)
{
	t_vec3	diffuse;
	t_vec3	light_dir;
	double	ratio;


	t_vec3   	specular;
    t_vec3      view_dir;
    t_vec3      reflect_dir;
    double      spec;
    double      ksn;
    double      ks;


	double		light_length;
	t_ray		light_ray;

	light_dir = vec3_unit(vec3_sub(ele->light->pos, rec->pos));
	ratio = fmax(vec3_dot(rec->norm, light_dir), 0.0);
	diffuse = vec3_dmul(ratio, vec3_set(0.3, 0.3, 0.3));


	view_dir = vec3_unit(vec3_dmul(-1, ele->ray->dir));
    reflect_dir = reflect(vec3_dmul(-1, light_dir), rec->norm);
    ksn = 64; // shininess value
    ks = 0.5; // specular strength
    spec = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), ksn);
    specular = vec3_dmul(spec, vec3_dmul(ks, vec3_set(1, 1, 1)));


	light_length = vec3_length(vec3_sub(ele->light->pos, rec->pos));
	light_ray.pos = vec3_add(rec->pos, vec3_dmul(1e-6, rec->norm));
	light_ray.dir = vec3_sub(ele->light->pos, rec->pos);
	if (in_shadow(ele, &light_ray))
		return (vec3_set(0, 0, 0));
    return (vec3_add(diffuse, specular));
}

t_vec3	phong_light(t_elements *ele, t_hit_record *rec)
{
	t_vec3	ret;
	t_vec3	ambient;

	rec->albedo = vec3_set(2, 2, 2);
	ambient = vec3_dmul(ele->amb->ratio, vec3_set((double)ele->amb->red / 255, (double)ele->amb->green / 255, (double)ele->amb->blue / 255));
	ret = vec3_set(0, 0, 0);
	ret = vec3_add(ret, point_light(ele, rec));
	ret = vec3_add(ret, ambient); // ambient
	return (vec3_min(vec3_mul(ret, rec->albedo), vec3_set(1, 1, 1)));
}
