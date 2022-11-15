/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:05:32 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/08 17:00:58 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

// t_ray	set_ray(t_elements ele, double aspect_ratio)
// {
// 	t_ray	ray;
// 	double	h;
// 	double	vp_height;
// 	double	vp_width;
// 	t_vec3	vup = vec3_set(1, 1, 1);

// 	h = tan(ele.cam.fov / 2);
// 	vp_height = 2.0 * h;
// 	vp_width = vp_height * aspect_ratio;

// 	t_vec3	w = vec3_unit(vec3_sub(ele.cam.pos, ele.cam.norm));
// 	t_vec3	u = vec3_unit(vec3_mul(vup, w));
// 	t_vec3	v = vec3_mul(w, u);


// 	t_vec3 hor = vec3_dmul(vp_width, u);
// 	t_vec3 ver = vec3_dmul(vp_height, v);
// 	t_vec3 low_left_corner = vec3_sub(vec3_sub(vec3_sub(ele.cam.pos, vec3_dmul(1 / 2, hor)), vec3_dmul(1 / 2, ver)), w);
// 	ray.pos = ele.cam.pos;
// 	ray.dir = vec3_sub(vec3_add(vec3_add(low_left_corner, vec3_mul(hor, u)), vec3_mul(ver, v)), ele.cam.pos);
// 	return (ray);
// }