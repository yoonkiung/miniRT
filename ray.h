/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:42:15 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/07 21:03:16 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector3.h"

typedef struct s_ray
{
	t_vec3	pos;
	t_vec3	dir;
}	t_ray;

t_vec3	ray_at(t_ray ray, double t)
{
	t_vec3 ret;

	ret.x = ray.pos.x + ray.dir.x * t;
	ret.y = ray.pos.y + ray.dir.y * t;
	ret.z = ray.pos.z + ray.dir.z * t;
	return (ret);
}

#endif