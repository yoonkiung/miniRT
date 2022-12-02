/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:45:11 by kiyoon            #+#    #+#             */
/*   Updated: 2022/12/02 15:45:12 by kiyoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT_bonus.h"

int	hit_cone(t_cone *co, t_ray *ray, t_hit_record *rec)
{
	t_vec3	ce;
	double	dv;
	double	ce_v;
	double	cp_len;

	ce = vec3_sub(ray->pos, co->point);
	dv = vec3_dot(ray->dir, co->normal);
	ce_v = vec3_dot(ce, co->normal);
	if (!cal_root(dv * dv - pow(cos(co->theta), 2),
			dv * ce_v - vec3_dot(ce, ray->dir) * pow(cos(co->theta), 2),
			ce_v * ce_v - vec3_dot(ce, ce) * pow(cos(co->theta), 2),
			rec))
		return (0);
	rec->pos = ray_at(ray, rec->t);
	cp_len = vec3_length(vec3_sub(rec->pos, co->point));
	//아직 미완성
	return (1);
}

void	hit_co(t_elements *ele, t_hit_record *rec, t_ray *ray, t_vec3 *ret)
{
	t_cone	*cur;

	cur = ele->cone;
	while (cur)
	{
		if (hit_cone(cur, ray, rec))
		{
			*ret = vec3_set(cur->red, cur->green, cur->blue);
			rec->tmax = rec->t;
		}
		cur = cur->next;
	}
}
