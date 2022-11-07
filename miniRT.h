/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:52:12 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/07 16:36:30 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "libft/libft.h"
#include <math.h>

typedef struct s_elements
{
	t_ambient	amb;
	t_camera	cam;
	t_light		light;
	t_sphere 	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	int			sphere_cnt;
	int			plane_cnt;
	int 		cylinder_cnt;
}	t_elements;

typedef struct s_ambient
{
	double	ratio;
	int		red;
	int		green;
	int		blue;
}	t_ambient;

typedef struct s_camera
{
	double	vp_x;
	double	vp_y;
	double	vp_z;
	double	norm_x;
	double	norm_y;
	double	norm_z;
	int		fov;
}	t_camera;

typedef struct s_light
{
	double	light_x;
	double	light_y;
	double 	light_z;
	double	ratio;
}	t_light;

typedef struct s_sphere
{
	double 	pos_x;
	double 	pos_y;
	double 	pos_z;
	double 	dia;
	int 	red;
	int 	green;
	int 	blue;
}	t_sphere;

typedef struct s_plane
{
	double 	pos_x;
	double	pos_y;
	double 	pos_z;
	double 	norm_x;
	double 	norm_y;
	double 	norm_z;
	int 	red;
	int 	green;
	int 	blue;
}	t_plane;

typedef struct s_cylinder
{
	double 	pos_x;
	double 	pos_y;
	double 	pos_z;
	double 	norm_x;
	double 	norm_y;
	double 	norm_z;
	double 	dia;
	double 	height;
	int 	red;
	int 	green;
	int 	blue;
}	t_cylinder;

#endif