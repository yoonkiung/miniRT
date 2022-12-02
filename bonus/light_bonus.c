/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:16:01 by kiyoon            #+#    #+#             */
/*   Updated: 2022/12/02 17:16:02 by kiyoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

t_vec3	reflect_bonus(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_dmul(vec3_dot(v, n) * 2, n)));
}

bool	in_shadow_bonus(t_elements *ele, t_ray *light_ray)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = INFINITY;
	if (hit_bonus(ele, &rec, light_ray).x != -1)
		return (true);
	return (false);
}

t_vec3	get_specular_bonus(t_elements *ele, t_hit_record *rec, t_vec3 light_dir)
{
	t_vec3	specular;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	double	spec;

	view_dir = vec3_unit(vec3_dmul(-1, ele->ray->dir));
	reflect_dir = reflect_bonus(vec3_dmul(-1, light_dir), rec->norm);
	spec = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 64);
	specular = vec3_dmul(spec, vec3_dmul(ele->light->ratio, \
		vec3_set((double)ele->light->red / 255, \
		(double)ele->light->green / 255, (double)ele->light->blue / 255)));
	return (specular);
}

t_vec3	point_light_bonus(t_elements *ele, t_hit_record *rec)
{
	t_vec3	diffuse;
	t_vec3	light_dir;
	double	ratio;
	double	light_length;
	t_ray	light_ray;

	light_dir = vec3_unit(vec3_sub(ele->light->pos, rec->pos));
	ratio = fmax(vec3_dot(rec->norm, light_dir), 0.05);
	diffuse = vec3_dmul(ratio, vec3_set((double)ele->light->red / 255, \
		(double)ele->light->green / 255, (double)ele->light->blue / 255));
	light_length = vec3_length(vec3_sub(ele->light->pos, rec->pos));
	light_ray.pos = vec3_add(rec->pos, vec3_dmul(EPSILON, rec->norm));
	light_ray.dir = vec3_sub(ele->light->pos, rec->pos);
	if (in_shadow_bonus(ele, &light_ray))
		return (vec3_set(0, 0, 0));
	return (vec3_add(diffuse, get_specular_bonus(ele, rec, light_dir)));
	return (diffuse);
}

t_vec3	phong_light_bonus(t_elements *ele, t_hit_record *rec)
{
	t_vec3	ret;
	t_vec3	ambient;

	ambient = vec3_dmul(ele->amb->ratio, vec3_set((double)ele->amb->red / 255, \
		(double)ele->amb->green / 255, (double)ele->amb->blue / 255));
	ret = vec3_set((double)ele->light->red / 255, \
		(double)ele->light->green / 255, (double)ele->light->blue / 255);
	ret = vec3_dmul(0.3, ret);
	ret = vec3_add(ret, point_light_bonus(ele, rec));
	ret = vec3_add(ret, ambient);
	return (vec3_min(vec3_dmul(ele->light->ratio, ret), vec3_set(1, 1, 1)));
}
