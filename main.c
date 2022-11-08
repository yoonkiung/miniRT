/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daechoi <daechoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:58:18 by kiyoon            #+#    #+#             */
/*   Updated: 2022/11/08 18:43:34 by daechoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>


typedef struct  s_img
{
    void    *img_ptr;
    char    *data;
    int     size_l;
    int     bpp;
    int     endian;
}   t_img;

int	exit_game(t_set *set)
{
	mlx_destroy_window(set->mlx, set->win);
	exit(0);
}

int	is_end_rt(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 1] == 't' && file[i - 2] == 'r' && file[i - 3] == '.')
		return (open(file, O_RDONLY));
	else
		return (0);
}

bool	split_type(char **temp, t_elements *element)
{
	if (ft_strcmp(temp[0], "A") == 0){
		if (!parse_a(temp, element))
			return (false);}
	else if (ft_strcmp(temp[0], "C") == 0){
		if (!parse_c(temp, element))
			return (false);}
	else if (ft_strcmp(temp[0], "L") == 0){
		if (!parse_l(temp, element))
			return (false);}
	else if (ft_strcmp(temp[0], "sp") == 0){
		if (!parse_sphere(temp, element))
			return (false);}
	else if (ft_strcmp(temp[0], "pl") == 0){
		if (!parse_plane(temp, element))
			return (false);}
	else if (ft_strcmp(temp[0], "cy") == 0){
		if (!parse_cylinder(temp, element))
			return (false);}
	else{
		return (false);}
	return (true);
}

int hit_sphere(t_sphere sp, t_ray ray)
{
    t_vec3   oc;
    double  a;
    double  b;
    double  c;
    double  discriminant;

    oc = vec3_sub(ray.pos, sp.pos);
    a = vec3_dot(ray.dir, ray.dir);
    b = vec3_dot(oc, ray.dir);
    c = vec3_dot(oc, oc) - ((sp.dia / 2) * (sp.dia / 2));
    discriminant = b * b - a * c;
	//printf("%f\n", discriminant);
    if (discriminant >= 0)
        return (1);
    else
        return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, t_ray *ray, t_sphere sp, t_elements *ele)
{
    int     rgb_color;
    char	*dst;

	(void)ray;
	// int r = 255;
	// int g = 255;
	// int b = 255;

	ele->cam->pos = vec3_set(0, 0, 0);
	double vp_h = 2.0;
	double vp_w = 16.0 / 9.0 * vp_h;
	double focal = 1.0;
	t_vec3 hor = vec3_set(vp_w, 0, 0);
	t_vec3 ver = vec3_set(0, vp_h, 0);
	t_vec3 llc = vec3_sub(vec3_sub(vec3_sub(ele->cam->pos, vec3_dmul(1 / 2, hor)), vec3_dmul(1 / 2, ver)), vec3_set(0, 0, focal));
	double u = (double)x / (double)(1600 - 1);
    double v = (double)y / (double)(900 - 1);
	ray->pos = ele->cam->pos;
	ray->dir = vec3_sub(vec3_add(vec3_add(llc, vec3_dmul(u, hor)), vec3_dmul(v, ver)), ray->pos);
    double t = 0.5 * (vec3_unit(ray->dir).y + 1.0);
    t_vec3 color = vec3_dmul(255.999, vec3_add(vec3_dmul( (1.0 - t), vec3_set(1.0, 1.0, 1.0)), \
                    vec3_dmul(t, vec3_set(0.5, 0.7, 1.0))));
	if (hit_sphere(sp, *ray))
	{
		color.x = 100;
		color.y = 0;
		color.z = 0;
	}
    rgb_color = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
    dst = img->data + (x * (img->bpp / 8)) + ((900 - y - 1) * img->size_l);
	*(unsigned int *)dst = rgb_color;
}

bool	split_newline(int fd, t_elements *element)
{
	char	*line;
	char	**temp;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "") != 0)
		{
			temp = ft_split(line, " ");
			if (!split_type(temp, element))
				return (false);
			free_char(temp);
		}
		free(line);
		line = get_next_line(fd);	
	}
	return (true);
}

void init_variable(t_elements *element)
{
	element->amb = NULL;
	element->cam = NULL;
	element->light = NULL;
	element->sphere = NULL;
	element->plane = NULL;
	element->cylinder = NULL;
	element->sphere_cnt = 0;
	element->plane_cnt = 0;
	element->cylinder_cnt = 0;
}

bool init(int ac, char **av, t_elements *element)
{
	int	fd;

	init_variable(element);
	if (ac != 2)
		return (false);
	fd = is_end_rt(av[1]);
	if (!fd)
		return (false);
	if(!split_newline(fd, element))
		return (false);
	return (true);
}




int main(int ac, char **av)
{
	t_elements	*ele = NULL;
	t_set 		set;
	t_img 		img;
	t_sphere	sph;
	t_ray		ray;
	//t_camera 	cam;

	(void)ac;
	(void)av;
	ele = ft_malloc(sizeof(t_elements));
	ele->cam = ft_malloc(sizeof(t_camera));
	set.mlx = mlx_init();
	set.win = mlx_new_window(set.mlx, 1600, 900, "miniRT");

	img.img_ptr = mlx_new_image(set.mlx, 1600, 900);
    img.data = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

    int count_h = 900;
	int count_w;
	sph.pos = vec3_set(1, 1, 0);
	sph.dia = 2.0;
	sph.red = 255;
	sph.green = 100;
	sph.blue = 255;
	// ele->cam->pos = vec3_set(0, 0, 0);
	// ele->cam->norm = vec3_set(1, 0, 0);
	// ele->cam->fov = 90;
	//ray = set_ray(ele, 1600 / 900);
    while (--count_h >= 0)
    {
        count_w = -1;
        while (++count_w < 1600)
		{
				my_mlx_pixel_put(&img, count_w, count_h, &ray, sph, ele);
		}
    }
    mlx_put_image_to_window(set.mlx, set.win, img.img_ptr, 0, 0);
	//mlx_hook(set.win, X_EVENT_KEYPRESS, 0, &exit_game, &set);
	mlx_hook(set.win, X_EVENT_DESTROYNOTIFY, 0, &exit_game, &set);
	mlx_loop(set.mlx);
	free(set.mlx);
}
