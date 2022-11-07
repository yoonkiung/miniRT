/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:52:12 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/07 19:55:50 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "libft/libft.h"
#include <math.h>
#include <mlx.h>
#include "vector3.h"

# define X_EVENT_KEYPRESS		2
# define X_EVENT_DESTROYNOTIFY	17

typedef struct s_set
{
	void	*mlx;
	void 	*win;
}	t_set;

typedef struct s_ambient
{
	double	ratio;
	int		red;
	int		green;
	int		blue;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	norm;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	pos;
	double	ratio;
}	t_light;

typedef struct s_sphere
{
	t_vec3	pos;
	double 	dia;
	int 	red;
	int 	green;
	int 	blue;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	pos;
	t_vec3	norm;
	int 	red;
	int 	green;
	int 	blue;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	pos;
	t_vec3	norm;
	double 	dia;
	double 	height;
	int 	red;
	int 	green;
	int 	blue;
}	t_cylinder;

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

#endif