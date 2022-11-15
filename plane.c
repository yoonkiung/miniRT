/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:55:05 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/15 18:55:06 by kiyoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_plane(t_plane *sp, t_ray *ray, t_hit_record *rec))

bool	hit_pl(t_elements *ele, t_hit_record *rec, t_ray *ray)
{
	bool	ishit;
	t_plane	*cur;

	ishit = false;
	cur = ele->plane;
	while (cur)
	{
		if (hit_plane(cur, ray, rec))
		{

		}
	}
	return (ishit);
}