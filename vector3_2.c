/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:01:56 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/08 16:33:24 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 ret;

	ret.x = vec1.x + vec2.x;
	ret.y = vec1.y + vec2.y;
	ret.z = vec1.z + vec2.z;
	return (ret);
}

t_vec3	vec3_mul(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 ret;

	ret.x = vec1.x * vec2.x;
	ret.y = vec1.y * vec2.y;
	ret.z = vec1.z * vec2.z;
	return (ret);
}

t_vec3	vec3_dmul(double d, t_vec3 vec)
{
	t_vec3 ret;

	ret.x = vec.x * d;
	ret.y = vec.y * d;
	ret.z = vec.z * d;
	return (ret);
}

t_vec3	vec3_unit(t_vec3 vec)
{
	t_vec3	ret;
	
	ret.x = vec.x / vec3_length(vec);
	ret.y = vec.y / vec3_length(vec);
	ret.z = vec.z / vec3_length(vec);
	return (ret);
}
#include <stdio.h>
void vec3_print(t_vec3 vec)
{
	printf("(%f, %f, %f)\n", vec.x, vec.y, vec.z);
}
