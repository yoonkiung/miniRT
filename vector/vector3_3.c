/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiyoon <kiyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:59:37 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/17 19:59:38 by kiyoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector3.h"

t_vec3	vec3_cross(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	cross;

	cross.x = vec1.y * vec2.z - vec1.z * vec2.y;
	cross.y = vec1.z * vec2.x - vec1.x * vec2.z;
	cross.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (cross);
}
