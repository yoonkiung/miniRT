/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:52:12 by daechoi           #+#    #+#             */
/*   Updated: 2022/11/09 20:48:57 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "vector3.h"
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "ray.h"

# define X_EVENT_KEYPRESS		2
# define X_EVENT_DESTROYNOTIFY	17

typedef struct s_hitten_object
{
	char					type;
	void 					*elements;
	struct s_hitten_object	*next;
}	t_hitten_object;

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
	t_vec3			pos;
	double 			dia;
	int 			red;
	int 			green;
	int 			blue;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	t_vec3			pos;
	t_vec3			norm;
	int 			red;
	int 			green;
	int 			blue;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3				pos;
	t_vec3				norm;
	double 				dia;
	double 				height;
	int 				red;
	int 				green;
	int 				blue;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_elements
{
	t_ambient	*amb;
	t_camera	*cam;
	t_light		*light;
	t_sphere 	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_ray		*ray;
	int			sphere_cnt;
	int			plane_cnt;
	int 		cylinder_cnt;
}	t_elements;

void	free_char(char **buffer);

int		parse_c(char **buffer, t_elements *element);

int		parse_a(char **buffer, t_elements *element);

int		parse_l(char **buffer, t_elements *element);

int		parse_plane(char **buffer, t_elements *element);

int		parse_cylinder(char **buffer, t_elements *element);

int		parse_sphere(char **buffer, t_elements *element);

void	ft_exit(int a);

int		is_end_rt(char *file);

bool	split_type(char **temp, t_elements *element);

bool	split_newline(int fd, t_elements *element);

void init_variable(t_elements *element);

bool init(int ac, char **av, t_elements *element);

#endif