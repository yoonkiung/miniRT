/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:44:45 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/21 16:38:32 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_select	*init_select(t_camera *cam, t_light *light)
{
	t_select	*select;

	select = ft_malloc(sizeof(t_select));
	select->type = CAM;
	select->cam = cam;
	select->light = light;
	select->sp = NULL;
	select->pl = NULL;
	select->cy = NULL;
	return (select);
}

void	hit_sp_select(t_set *set, t_hit_record *rec, t_ray *ray)
{
	t_sphere	*cur;

	cur = set->ele->sphere;
	while (cur)
	{
		if (hit_sphere(cur, ray, rec))
		{
			set->select->type = SPHERE;
			set->select->sp = cur;
			rec->tmax = rec->t;
		}
		cur = cur->next;
	}
}

void	hit_pl_select(t_set *set, t_hit_record *rec, t_ray *ray)
{
	t_plane	*cur;

	cur = set->ele->plane;
	while (cur)
	{
		if (hit_plane(cur, ray, rec))
		{
			set->select->type = PLANE;
			set->select->pl = cur;
			rec->tmax = rec->t;
		}
		cur = cur->next;
	}
}

void	ray_select(t_set *set, t_ray *ray)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = INFINITY;
	hit_sp_select(set, &rec, ray);
	hit_pl_select(set, &rec, ray);
}

t_select	*select_object(t_set *set)
{
	t_ray	ray;
	double	u;
	double	v;

	u = (double)set->select->mouse_x / (double)(WIDTH - 1);
	v = (double)set->select->mouse_y / (double)(HEIGHT - 1);
	init_camera(set->ele->cam);
	ray.pos = set->ele->cam->pos;
	ray.dir = vec3_unit(vec3_sub(vec3_add(vec3_add(set->ele->cam->llc, \
		vec3_dmul(u, set->ele->cam->hor)), \
		vec3_dmul(v, set->ele->cam->ver)), \
		ray.pos));
	ray_select(set, &ray);
	return (set->select);
}
